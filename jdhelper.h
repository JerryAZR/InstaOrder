#ifndef JDHELPER_H
#define JDHELPER_H

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QWebEnginePage>
#include <QWebEngineScript>
#include <QTimer>
#include <QElapsedTimer>
#include <QMap>
#include <QSet>
#include <QRegularExpression>
#include "jdorderconfig.h"
#include "orderhelper.h"
#include "qrcodedialog.h"

/**
 * @brief The JDHelper class
 *
 * An OrderHelper class targeting jd.com
 *
 * Two ordering modes are provided in version 0.3.0
 *      auto (advancedMode = false) : QWebEngine based
 *      manual (advancedMode = true): QNetworkAccessManager based
 *
 * In auto mode, all parameters needed for order submission are automatically
 * obtained from the order info page (after the javascripts have done executing).
 *
 * In manual mode, some of these parameters must be obtained by user ahead of time.
 */
class JDHelper : public OrderHelper
{
    Q_OBJECT
public:
    constexpr static const char USER_AGENT[] ="Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/114.0.0.0 Safari/537.36 Edg/114.0.1823.67";
    constexpr static const char SEC_CH_UA[] = R"("Not.A/Brand";v="8", "Chromium";v="114", "Microsoft Edge";v="114")";
    constexpr static const char SEC_CH_UA_MOBILE[] = "?0";
    constexpr static const char SEC_CH_UA_PLATFORM[] = R"("Windows")";

    QNetworkAccessManager accessManager;
    QWebEnginePage *page;           // For generic browsing
    QWebEnginePage *orderPage;      // For placing orders only
    QrCodeDialog *qrCodeView;       // For displaying log-in QR code
    QWebEngineScript orderScript;   // Auto order-submission sript
    QTimer *keepAliveTimer;         // Refresh periodically to stay logged in
    QElapsedTimer perfTimer;        // For performance profiling
    // Manual mode parameters
    JDOrderConfig *config;
    bool advancedMode = false;
    QString uuid;
    QString eid;
    QString fp;

    explicit JDHelper(QWidget *parent = nullptr);
    ~JDHelper() {/* Every object has a parent. Nothing to delete manually. */}

    // OrderHelper interface
public:
    void buy_item(QString itemId, int itemCnt);
    void log_in();
    void get_item_detail(const QString &itemId);
    void show_config();


    /**
     * @brief analyze_home_page
     * @param html  document of home.jd.com
     *
     * This function extracts username from home.jd.com
     */
    void analyze_home_page(const QString &html);

    /**
     * @brief analyze_item_page
     * @param html  document of item.jd.com/<item-id>.html
     *
     * This function extracts various product information from item page.
     */
    void analyze_item_page(const QString &html);

    /**
     * @brief request_item_detail
     * @param itemId
     *
     * Send an HTTP GET request for
     * https://item.jd.com/<itemId>.html
     */
    void request_item_detail(const QString &itemId);

    /**
     * @brief request_checkout
     *
     * Send an HTTP GET request for
     * https://trade.jd.com/shopping/order/getOrderInfo.action
     */
    void request_checkout();

    /**
     * @brief request_submit_order
     *
     * Send an HTTP POST request (with some user-defined data) to submit order.
     */
    void request_submit_order();

    /**
     * @brief browserGet
     * @param request
     * @return reply
     *
     * Sets additional headers before sending the request,
     * to emulate a common browser.
     */
    QNetworkReply * browserGet(QNetworkRequest& request);
    QNetworkReply * browserPost(QNetworkRequest& request, const QByteArray& payload);

    /**
     * @brief handle_return_code
     * @param code
     *
     * Intepret JD and custom return code and report order status accordingly.
     */
    void handle_return_code(int code);

public slots:
    void _on_cookie_add(const QNetworkCookie &cookie);
    void _on_page_load();
    void _on_url_change(const QUrl &url);
    void _order_next_step(const QUrl &url);
    void _reload();
    void _update_manual_config(int result);

signals:
    void pageReady();
};

#endif // JDHELPER_H
