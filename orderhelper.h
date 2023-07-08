#ifndef ORDERHELPER_H
#define ORDERHELPER_H

#include <QObject>
#include <QPixmap>

class OrderHelper : public QObject
{
    Q_OBJECT
public:
    explicit OrderHelper(QObject *parent = nullptr) {};
    virtual void buy_item(QString itemId, int itemCnt) = 0;
    virtual void log_in() = 0;
    virtual void get_item_detail(QString itemId) = 0;

signals:
    void qrCodeReady(QPixmap *img);
    void imageReady(QPixmap *img);
    void loggedIn();

};

#endif // ORDERHELPER_H
