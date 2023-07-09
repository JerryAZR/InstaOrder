#ifndef JDHELPER_H
#define JDHELPER_H

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QWebEnginePage>
#include <QWebEngineScript>
#include <QTimer>
#include <QMap>
#include <QSet>
#include <QRegularExpression>
#include "orderhelper.h"
#include "qrcodedialog.h"

class JDHelper : public OrderHelper
{
    Q_OBJECT
public:
    // __jda = 122270672.16887432941561768025258.1688743294.1688743294.1688743294.1
    constexpr static const char USER_AGENT[] ="Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/114.0.0.0 Safari/537.36 Edg/114.0.1823.67";
    constexpr static const char SEC_CH_UA[] = R"("Not.A/Brand";v="8", "Chromium";v="114", "Microsoft Edge";v="114")";
    constexpr static const char SEC_CH_UA_MOBILE[] = "?0";
    constexpr static const char SEC_CH_UA_PLATFORM[] = R"("Windows")";
    constexpr static const auto RAW_PARAM_NAMES = {"sopNotPutInvoice",
                                                   "TrackID", "regionId", "shopId", "easyBuyFlag", "ignorePriceChange",
                                                   "eid", "fp", "flowType", "riskControl", "isBestCoupon", "appraisalbuyCheck",
                                                   "giftRemoveType", "limitUserFlag"};

    QNetworkAccessManager accessManager;
    QWebEnginePage *page;       // For generic browsing
    QWebEnginePage *orderPage;  // For placing orders only
    QrCodeDialog *qrCodeView;
    QWebEngineScript orderScript;
    QTimer *keepAliveTimer;

    explicit JDHelper(QWidget *parent = nullptr);
    ~JDHelper() {/* Every object has a parent. Nothing to delete manually. */}

    // OrderHelper interface
public:
    void buy_item(QString itemId, int itemCnt);
    void log_in();
    void get_item_detail(const QString &itemId);

    void analyze_home_page(const QString &html);
    void analyze_item_page(const QString &html);
    void request_item_detail(const QString &itemId);
    QNetworkReply * browserGet(QNetworkRequest& request);
    QNetworkReply * browserPost(QNetworkRequest& request, QByteArray& payload);

public slots:
    void _on_cookie_add(const QNetworkCookie &cookie);
    void _on_page_load();
    void _on_url_change(const QUrl &url);
    void _order_next_step(const QUrl &url);
    void _reload();

signals:
    void pageReady();
};

#endif // JDHELPER_H
