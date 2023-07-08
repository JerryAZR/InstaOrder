#ifndef JDHELPER_H
#define JDHELPER_H

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QWebEnginePage>
#include <QTimer>
#include <QMap>
#include <QSet>
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
    QWebEnginePage *page;
    QrCodeDialog *qrCodeView;
    QTimer statusChecker;
    QMap<QString, QString> cookieJar;
    QSet<QString> orderParamNames;
    QMap<QString, QString> orderParams;

    explicit JDHelper(QObject *parent = nullptr);
    ~JDHelper() {delete qrCodeView;}

    // OrderHelper interface
public:
    void buy_item(QString itemId, int itemCnt);
    void log_in();
    void get_item_detail(QString itemId);

    void do_log_in();
    void validate_ticket(QString ticket);
    void save_cookies(const QUrl &url);
    void request_checkout();
    void request_submit_order(QNetworkReply *reply);
    QByteArray combine_params();
    QNetworkReply * browserGet(QNetworkRequest& request);
    QNetworkReply * browserPost(QNetworkRequest& request, QByteArray& payload);
    QDialog *showWidget(QWidget *widget);

public slots:
    void check_status();
    void add_cookie(const QNetworkCookie &cookie);
    void _on_page_load();
    void _on_url_change(const QUrl &url);
};

#endif // JDHELPER_H
