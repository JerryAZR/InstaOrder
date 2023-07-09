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
    virtual void get_item_detail(const QString &itemId) = 0;

signals:
    // item info
    void imageReady(QPixmap *img);
    void imageSrcReady(const QString &src);
    void itemNameReady(const QString &name);
    void itemPriceReady(const QString &price);
    void itemStatusReady(const QString &status);
    void shopNameReady(const QString &shop);
    void progressUpdated(int progress);
    // log-in
    void qrCodeReady(QPixmap *img);
    void loggedIn(const QString &username);
    // order
    void orderFinished(bool success);

};

#endif // ORDERHELPER_H
