#include "jdhelper.h"
#include "urls.h"
#include <QRegularExpression>
#include <QRandomGenerator>
#include <QNetworkCookieJar>
#include <QNetworkCookie>
#include <QWebEngineProfile>
#include <QWebEngineCookieStore>
// Debug libs
#include <QWebEngineView>
#include <QDialog>
#include <QVBoxLayout>

#include <QDateTime>
#include <QJsonDocument>
#include <QJsonObject>

JDHelper::JDHelper(QObject *parent)
    : OrderHelper{parent}
{
    QWebEngineView * testView = new QWebEngineView;
    testView->setMinimumSize(800,600);
    showWidget(testView);

    qrCodeView = new QrCodeDialog;

//    _page = new QWebEnginePage;
    page = testView->page();
    statusChecker.setInterval(2000);

    // Initialize the QSet to be used later for filtering useful info from html
    foreach (const char* name, RAW_PARAM_NAMES) {
        orderParamNames.insert(name);
    }

    connect(&statusChecker, &QTimer::timeout, this, &JDHelper::check_status);
    connect(page, &QWebEnginePage::loadFinished, this, &JDHelper::_on_page_load);
    connect(page, &QWebEnginePage::urlChanged, this, &JDHelper::_on_url_change);
    connect(page, &QWebEnginePage::urlChanged, this, [](const QUrl &url){qDebug() << "Page url changed to " << url;});
    connect(page->profile()->cookieStore(), &QWebEngineCookieStore::cookieAdded, this, &JDHelper::add_cookie);

    // Log-in QR code display control
    connect(qrCodeView, &QDialog::accepted, this, &JDHelper::log_in);
    connect(this, &JDHelper::loggedIn, qrCodeView, &QDialog::hide);
}

void JDHelper::buy_item(QString itemId, int itemCnt)
{
//    QNetworkRequest request(QUrl(QString(JD::addItemUrl).arg(itemId).arg(itemCnt)));
//    request.setRawHeader("Referer", "https://item.jd.com/");
//    QNetworkReply * reply = browserGet(request);
//    connect(reply, &QNetworkReply::finished, this, [this, reply](){
//        if (reply->url().matches(QUrl(JD::addItemUrl), JD::domainCompareRules)) {
//            qDebug() << "Added to cart";
//            request_checkout();
//        } else {
//            qDebug() << "Item not added to cart. Got this url instead:";
//            qDebug() << "reply url:" << reply->url();
//        }
//        reply->close();
//        reply->deleteLater();
//    });
    QUrl url(QString(JD::addItemUrl).arg(itemId).arg(itemCnt));
    page->load(url);
}

void JDHelper::do_log_in()
{
    qDebug() << "Trying to log-in";
    QUrl codeSrc(QString(JD::qrCodeSrc).arg(QDateTime::currentMSecsSinceEpoch()));
    QNetworkRequest request;
    request.setUrl(codeSrc);
    request.setRawHeader("Referer", "https://passport.jd.com/");
    QNetworkReply *reply = browserGet(request);
    connect(reply, &QNetworkReply::finished, this, [this, reply](){
        qDebug() << "Got response";
        qDebug() << reply->url();
        qDebug() << reply->header(QNetworkRequest::SetCookieHeader);
        save_cookies(QUrl(JD::loginUrl).adjusted(JD::domainCompareRules));
        QPixmap *img = new QPixmap();
        if (!img->loadFromData(reply->readAll(), "png")) {
            qFatal() << "Failed to get log-in code";
        }
        emit qrCodeReady(img);
        reply->close();
        reply->deleteLater();
        statusChecker.start();
    });
}

void JDHelper::_on_page_load()
{
    qDebug() << "Got page";
    QUrl url = page->url();
    if (url.matches(QUrl(JD::loginUrl), JD::domainCompareRules)) {
//        do_log_in();
        qrCodeView->set_source(QString(JD::qrCodeSrc).arg(QDateTime::currentMSecsSinceEpoch()));
        qrCodeView->show();
    }
    else {
        qDebug() << "Page loaded:" << url;
    }
}

void JDHelper::_on_url_change(const QUrl &url)
{
    // If at cart, go to checkout page
    if (url.matches(QUrl(JD::addItemUrl), JD::domainCompareRules)) {
        page->load(QUrl(JD::checkoutUrl));
    }

    // If at checkout page, get html (for debugging)
    if (url.matches(QUrl(JD::checkoutUrl), JD::fileCompareRules)) {
        qDebug() << "Preparing html";
        page->toHtml([](const QString &html){
            qDebug() << "Displaying html";
            qDebug() << html;
        });
    }

    if (url.matches(QUrl(JD::homeUrl), JD::domainCompareRules)) {
        emit loggedIn();
    }

    // If at log-in page, show a spinner and wait for QR code
    if (url.matches(QUrl(JD::loginUrl), JD::fileCompareRules)) {
        qrCodeView->set_spinner();
        qrCodeView->show();
    }
}

void JDHelper::validate_ticket(QString ticket)
{
    QNetworkRequest request;
    request.setRawHeader("Referer", "https://passport.jd.com/");
    request.setUrl(QUrl(QString(JD::ticketUrl).arg(ticket)));
    QNetworkReply * reply = browserGet(request);
    connect(reply, &QNetworkReply::finished, this, [this, reply](){
        QByteArray content = reply->readAll();
        QJsonParseError error;
        QJsonDocument json = QJsonDocument::fromJson(content, &error);
        if (json.isObject()) {
            int returnCode = json.object().value("returnCode").toInt(-1);
            if (returnCode == 0) {
                qDebug() << "Logged in XD";
                emit loggedIn();
            } else {
                qCritical() << "Got non-zero return code" << returnCode;
            }
        } else {
            qCritical() << "Json parse error:" << error.errorString();
        }
    });
}

void JDHelper::save_cookies(const QUrl &url)
{
    QNetworkCookieJar *cookies = accessManager.cookieJar();
    foreach (QNetworkCookie cookie, cookies->cookiesForUrl(url)) {
        cookieJar.insert(cookie.name(), cookie.value());
        qDebug() << "Cookie " << cookie.name() << "=" << cookie.value();
    }
}

void JDHelper::get_item_detail(QString itemId)
{
}

void JDHelper::log_in()
{
    // First go to www.jd.com to grab necessary cookies
//    QNetworkRequest request;
//    request.setUrl(QUrl(JD::mainUrl));
//    QNetworkReply * reply = browserGet(request);
//    do_log_in();
    page->load(QUrl(JD::homeUrl));
}

void JDHelper::request_checkout()
{
    QNetworkRequest request((QUrl(JD::checkoutUrl)));
    request.setRawHeader("Referer", "https://cart.jd.com/");
    QNetworkReply * reply = browserGet(request);
    connect(reply, &QNetworkReply::finished, this, [this, reply](){
        if (reply->url().matches(QUrl(JD::checkoutUrl), JD::fileCompareRules)) {
            request_submit_order(reply);
        } else {
            qDebug() << "Did not get checkout page. Got this url instead:";
            qDebug() << "reply url:" << reply->url();
        }
        reply->close();
        reply->deleteLater();
    });
}

void JDHelper::request_submit_order(QNetworkReply *reply)
{
    static const QRegularExpression regex("<input[^<>]+id=\"([^<>\"]+)\"[^<>]+value=\"([^<>\"]+)\"[^<>]*>");
    qDebug() << "one step ahead!";
    QByteArray data = reply->readAll();
    QRegularExpressionMatchIterator iter = regex.globalMatch(data);
    orderParams.clear();
    while (iter.hasNext()) {
        QRegularExpressionMatch match = iter.next();
        if (orderParamNames.contains(match.captured(1))) {
            orderParams.insert(match.captured(1), match.captured(2));
            qDebug() << match.captured(1) << match.captured(2);
        }
    }
    QByteArray payload = combine_params();
    QNetworkRequest request;
    request.setUrl(QUrl(JD::submitUrl));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    request.setRawHeader("Referer", "https://trade.jd.com/");
    QNetworkReply * postReply = browserPost(request, payload);
    connect(postReply, &QNetworkReply::finished, this, [postReply](){
        qDebug() << "Got reply for post";
        qDebug() << postReply->url();
        qDebug() << postReply->readAll();
    });

//    QFile checkoutPage;
//    checkoutPage.setFileName("checkout.html");
//    checkoutPage.open(QFile::WriteOnly);
//    checkoutPage.write(data);
    //    checkoutPage.close();
}

QByteArray JDHelper::combine_params()
{
    QByteArray params;
    QByteArray value;

    value = orderParams.value("sopNotPutInvoice", "false").toLocal8Bit();
    params += QByteArray("submitOrderParam.sopNotPutInvoice=") + value;

    if (orderParams.contains("TrackID")) {
        value = orderParams.value("TrackID").toLocal8Bit();
        params += QByteArray("&submitOrderParam.trackID=") + value;
    }

    // useColorApi is treated as 0 because I can't find cookie __jda
//    if (submitOrderColorFLag == "1") {
//        actionUrl = useColorApi(actionUrl);
//        var useColorFlag = $("#useColorApi").val();
//        if (useColorFlag == "1") {
//            actionUrl = actionUrl + "&cthr=1"
//        }
//        param = getBody(param);
//    }

    if (orderParams.contains("regionId")) {
        value = orderParams.value("regionId").toLocal8Bit();
        params += QByteArray("&regionId=") + value;
    }
    if (orderParams.contains("shopId")) {
        value = orderParams.value("shopId").toLocal8Bit();
        params += QByteArray("&shopId=") + value;
    }

    value = orderParams.value("easyBuyFlag").toLocal8Bit();
    if (value == "1" || value == "2") {
        params += QByteArray("&ebf=") + value;
    }

    if (orderParams.contains("ignorePriceChange")) {
        value = orderParams.value("ignorePriceChange").toLocal8Bit();
        params += QByteArray("&submitOrderParam.ignorePriceChange=") + value;
    }
    params += QByteArray("&submitOrderParam.btSupport=0"); // Baitiao not supported

    if (orderParams.contains("eid")) {
        value = orderParams.value("eid").toLocal8Bit();
        params += QByteArray("&submitOrderParam.eid=") + value;
    } else {
        qWarning() << "Missing eid";
    }
    if (orderParams.contains("fp")) {
        value = orderParams.value("fp").toLocal8Bit();
        params += QByteArray("&submitOrderParam.fp=") + value;
    } else {
        qWarning() << "Missing fp";
    }

//    if ($("#flowType").val() == 15) {
//        var preMainSku = $('.goods-list .goods-items .goods-item');
//        if (preMainSku !== 'undefined') {
//            var preMainSkuId = preMainSku[0].getAttribute('goods-id');
//            if (preMainSkuId) {
//                param += "&submitOrderParam.preMainSkuId=" + preMainSkuId;
//            }
//        }
//    }
    value = orderParams.value("flowType", "0").toLocal8Bit();
    if (value == "15") {
        qCritical() << "TODO: add skuid";
    }

    if (orderParams.contains("riskControl")) {
        value = orderParams.value("riskControl").toLocal8Bit();
        params += QByteArray("&riskControl=") + value;
    }

//    var isBestCoupon = $('#isBestCoupon').val();
//    if (isBestCoupon) {
//        param += "&submitOrderParam.isBestCoupon=" + isBestCoupon;
//    }
    if (orderParams.contains("isBestCoupon")) {
        value = orderParams.value("isBestCoupon").toLocal8Bit();
        params += QByteArray("&submitOrderParam.isBestCoupon=") + value;
    }

    params += QByteArray("&submitOrderParam.jxj=1");

        //正品鉴定
//        if ($("#appraisalbuy").is(":checked")) {
//        param += "&submitOrderParam.zpjd=1";
//    } else {
//        param += "&submitOrderParam.zpjd=0";
//    }appraisalbuyCheck
    value = orderParams.value("appraisalbuyCheck", "0").toLocal8Bit();
    params += QByteArray("&submitOrderParam.zpjd=") + value;

    //移除赠品限购
    value = orderParams.value("giftRemoveType", "0").toLocal8Bit();
    params += QByteArray("&submitOrderParam.giftRemove=") + value;
    value = orderParams.value("limitUserFlag", "0").toLocal8Bit();
    params += QByteArray("&submitOrderParam.limitUserFlag=") + value;

    return params;
}

QNetworkReply *JDHelper::browserGet(QNetworkRequest &request)
{
    request.setHeader(QNetworkRequest::UserAgentHeader, USER_AGENT);
    request.setRawHeader("sec-ch-ua", SEC_CH_UA);
    request.setRawHeader("sec-ch-ua-mobile", SEC_CH_UA_MOBILE);
    request.setRawHeader("sec-ch-ua-platform", SEC_CH_UA_PLATFORM);
    return accessManager.get(request);
}

QNetworkReply *JDHelper::browserPost(QNetworkRequest &request, QByteArray &payload)
{
    request.setHeader(QNetworkRequest::UserAgentHeader, USER_AGENT);
    request.setRawHeader("sec-ch-ua", SEC_CH_UA);
    request.setRawHeader("sec-ch-ua-mobile", SEC_CH_UA_MOBILE);
    request.setRawHeader("sec-ch-ua-platform", SEC_CH_UA_PLATFORM);
    return accessManager.post(request, payload);
}

QDialog *JDHelper::showWidget(QWidget *widget)
{
    QDialog * dlg = new QDialog;
    QLayout * layout = new QVBoxLayout;
    layout->addWidget(widget);
    dlg->setLayout(layout);
    dlg->setSizePolicy(QSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum));
    dlg->show();
    return dlg;
}

/**
 * @brief JDHelper::checkStatus
 * Check if logged in
 */
void JDHelper::check_status()
{
    int rand = QRandomGenerator::global()->bounded(1000000, 9999999);
    if (!cookieJar.contains("wlfstk_smdl")) {
        qDebug() << "cookie not ready";
        return;
    }
    QString token = cookieJar.value("wlfstk_smdl");
    qint64 msec = QDateTime::currentMSecsSinceEpoch();
    QUrl target(QString(JD::statusUrl).arg(rand).arg(token).arg(msec));
    QNetworkRequest request;
    request.setUrl(target);
    request.setRawHeader("Referer", "https://passport.jd.com/");
    QNetworkReply *reply = browserGet(request);
    connect(reply, &QNetworkReply::finished, this, [this, reply](){
        QByteArray content = reply->readAll();
        content = content.remove(0, content.indexOf('{'));
        content = content.first(content.lastIndexOf('}')+1);
        qDebug() << "Raw" << QString(content);
        QJsonParseError error;
        QJsonDocument json = QJsonDocument::fromJson(content, &error);
        if (json.isObject()) {
            QJsonValue code = json.object().value("code");
            QJsonValue msg = json.object().value("msg");
            switch (code.toInt(-1)) {
            case 200:
                statusChecker.stop();
                // Go validate ticket
                validate_ticket(json.object().value("ticket").toString());
                break;
            case 201:
                // Code not yet scanned. Nothing to do
                break;
            case 202:
                // Code scanned. Waiting for confirm
                break;
            case 203:
                // Code expired. Get again
                do_log_in();
                break;
            default:
                qWarning() << msg;
                break;
            }
        } else {
            statusChecker.stop();
            qFatal() << error.errorString();
        }
        reply->close();
        reply->deleteLater();
    });
}

void JDHelper::add_cookie(const QNetworkCookie &cookie)
{
    cookieJar.insert(cookie.name(), cookie.value());
    if (accessManager.cookieJar()->insertCookie(cookie))
        qDebug() << "Cookie" << cookie.name() << ":" << cookie.value() << "Added";
    else
        qDebug() << "Cookie" << cookie.name() << ":" << cookie.value() << "Failed to add";
}
