#ifndef ORDERHELPER_H
#define ORDERHELPER_H

#include <QObject>
#include <QPixmap>

class OrderHelper : public QObject
{
    Q_OBJECT
public:
    explicit OrderHelper(QObject *parent = nullptr) {};

    /**
     * @brief buy_item
     * @param itemId    Unique identifier of the item to buy
     * @param itemCnt   number of items to buy
     *
     * This function must be imiplemented by derived classes.
     * It should at least handle the entire process of buying an item.
     * For example, three steps are needed for jd.com:
     *  (1) add item to cart
     *  (2) checkout (get order info page)
     *  (3) submit order
     * Ideally, the derived class should also handle status/result reporting.
     */
    virtual void buy_item(QString itemId, int itemCnt) = 0;

    /**
     * @brief log_in
     * Ask the user to enter log-in credentials, scan a QR code, or use any
     * other authentication method. Required for derived classes.
     */
    virtual void log_in() = 0;

    /**
     * @brief get_item_detail
     * @param itemId    Unique identifier of the item to buy
     *
     * Fetch item information frrom online, and report to UI (MainWindow)
     * using signals defined below.
     */
    virtual void get_item_detail(const QString &itemId) {};

    /**
     * @brief show_config
     *
     * If the derived class has multiple ordering modes, implement this
     * function to show a settings window.
     */
    virtual void show_config() {};

signals:
    // item info
    /**
     * @brief imageReady
     * @param img   Image preview (bitmap) of the item
     *
     * Instruct MainWindow to show the given image to user (unused in v0.3.0).
     */
    void imageReady(QPixmap *img);

    /**
     * @brief imageSrcReady
     * @param src   Image preview (source url) of the item
     *
     * Instruct MainWindow to download image from src, then show it to user.
     */
    void imageSrcReady(const QString &src);

    /**
     * @brief itemNameReady
     * @param name  String to display as item name
     *
     * Instruct MainWindow to display the given string as item name.
     */
    void itemNameReady(const QString &name);

    /**
     * @brief itemPriceReady
     * @param price Unit price of the item
     *
     * Instruct MainWindow to display the given string as item unit price.
     */
    void itemPriceReady(const QString &price);

    /**
     * @brief itemStatusReady
     * @param status    Item status
     *
     * Instruct MainWindow to display the given string as item status.
     * Originally intended for item stock, but can be used for other purposes.
     */
    void itemStatusReady(const QString &status);

    /**
     * @brief shopNameReady
     * @param shop  Name of the shop selling the item
     *
     * Instruct MainWindow to display the given string as shop name.
     */
    void shopNameReady(const QString &shop);

    /**
     * @brief progressUpdated
     * @param progress  range 0-100
     *
     * Instruct MainWindow to update progress bar to the given progress.
     */
    void progressUpdated(int progress);

    // log-in
    /**
     * @brief qrCodeReady
     * @param img
     *
     * Same as imageReady, unused in v0.3.0.
     */
    void qrCodeReady(QPixmap *img);

    /**
     * @brief loggedIn
     * @param username
     *
     * Instruct MainWindow to display the given string as username.
     * The "buy item" button in MainWindow is disabled on startup,
     * emitting this signal would enable that button.
     */
    void loggedIn(const QString &username);

    // order
    /**
     * @brief orderFinished
     * @param success
     *
     * This signal marks the completion of an order.
     */
    void orderFinished(bool success);

};

#endif // ORDERHELPER_H
