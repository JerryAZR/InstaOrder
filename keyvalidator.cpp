#include "keyvalidator.h"
#include <QDataStream>
#include <QDebug>

keyValidator::keyValidator()
{
    filter = BloomFilter();
    deadline = 0;
}

qint64 keyValidator::getDeadline() const
{
    return deadline;
}

void keyValidator::setDeadline(qint64 newDeadline)
{
    deadline = newDeadline;
}

bool keyValidator::updateKey(const QString &key)
{
    const QByteArray publicKey = QByteArray::fromBase64(
        "LS0tLS1CRUdJTiBQVUJMSUMgS0VZLS0tLS0KTUZrd0V3WUhLb1pJemowQ0FRWUlLb1pJemowREFRY0RRZ0FFQmJscXVtTXlSOXZHTmJXTUxneWZjNFZGTllrLwpNYnMzSm5EZzJCb0J0R3lvQzM0U0JVNXMzQ0JlejVrTFUzcXBScm9MT3V2S0FzRjI2MmNUb1VrMldRPT0KLS0tLS1FTkQgUFVCTElDIEtFWS0tLS0tCg=="
        );
    QByteArray rawKey;
    QByteArray oldHash;
    qint64 tmp_deadline;
    qint64 tmp_filterBase;
    rawKey = QByteArray::fromBase64(key.toUtf8());
    QDataStream ds(rawKey);
    ds >> tmp_deadline;
    ds >> tmp_filterBase;
    ds >> oldHash;
    if (crypto.checkSign(rawKey.first(2*sizeof(qint64)), oldHash, publicKey)) {
        filter.setFilter(tmp_filterBase);
        deadline = tmp_deadline;
        return true;
    } else {
        return false;
    }
}

bool keyValidator::validateId(const QString &id)
{
    return filter.contains(id.trimmed());
}

bool keyValidator::validateTime(qint64 timestamp)
{
    return timestamp < deadline;
}
