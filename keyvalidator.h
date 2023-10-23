#ifndef KEYVALIDATOR_H
#define KEYVALIDATOR_H

#include <QString>
#include <easyssl/ecdsassl.h>
#include "bloomfilter.h"

class keyValidator
{
public:
    keyValidator();

    BloomFilter filter;
    qint64 deadline;
    EasySSL::ECDSASSL crypto;

    bool updateKey(const QString &key);
    bool validateId(const QString &id);
    bool validateTime(qint64 timestamp);
    qint64 getDeadline() const;
    void setDeadline(qint64 newDeadline);
};

#endif // KEYVALIDATOR_H
