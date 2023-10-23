#ifndef BLOOMFILTER_H
#define BLOOMFILTER_H

#include <QString>

class BloomFilter
{
public:
    BloomFilter(int nbits = 64, int nhash = 6);

    qint64 filter;
    int nbits;
    int nhash;

    void addItem(const QString &item);
    bool contains(const QString &item);
    qint64 getFilter() const;
    void setFilter(qint64 newFilter);
};

#endif // BLOOMFILTER_H
