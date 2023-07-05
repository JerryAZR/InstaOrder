#ifndef ORDERINFO_H
#define ORDERINFO_H

#include <QObject>

class OrderInfo : public QObject {
    Q_OBJECT
public:
    QString itemId;
    int itemCount;
    qint64 orderTimeMSec;
    OrderInfo(QString id = "", int cnt = 0, qint64 msec = 0) :
        itemId(id), itemCount(cnt), orderTimeMSec(msec) {}
    ~OrderInfo() {}
};

#endif // ORDERINFO_H
