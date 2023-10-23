#include "bloomfilter.h"
#include <QHash>
#include <QDebug>

BloomFilter::BloomFilter(int nbits, int nhash)
{
    this->nbits = nbits;
    this->nhash = nhash;
    this->filter = 0;
}

qint64 BloomFilter::getFilter() const
{
    return filter;
}

void BloomFilter::setFilter(qint64 newFilter)
{
    filter = newFilter;
}

void BloomFilter::addItem(const QString &item)
{
    for (int i = 0; i < nhash; i++) {
        int offset = qHash(item.toLongLong(), i) % nbits;
        qint64 bitmask = ((qint64)1) << offset;
        filter |= bitmask;
    }
}

bool BloomFilter::contains(const QString &item)
{
    for (int i = 0; i < nhash; i++) {
        int offset = qHash(item.toLongLong(), i) % nbits;
        qint64 bitmask = ((qint64)1) << offset;
        if ((filter & bitmask) == 0) {
            return false;
        }
    }
    return true;
}
