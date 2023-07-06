#ifndef ORDERINFO_H
#define ORDERINFO_H

#include <QObject>
#include <QListWidgetItem>

class OrderInfo : public QObject {
    Q_OBJECT
public:
    QString itemId;
    int itemCount;
    qint64 orderTimeMSec;
    QListWidgetItem * listItem;
    OrderInfo(QString id = "", int cnt = 0, qint64 msec = 0) :
        itemId(id), itemCount(cnt), orderTimeMSec(msec), listItem(nullptr) {}
    ~OrderInfo() {}
};

#endif // ORDERINFO_H
