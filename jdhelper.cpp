#include "jdhelper.h"
#include "qwebenginescriptcollection.h"
#include "urls.h"
//#include <QRandomGenerator>
#include <QNetworkCookieJar>
#include <QNetworkCookie>
#include <QWebEngineProfile>
#include <QWebEngineCookieStore>
#include <QDialog>
#include <QDateTime>
#include <QFile>
#include <QMessageBox>
//#include <QJsonDocument>
//#include <QJsonObject>

JDHelper::JDHelper(QWidget *parent)
    : OrderHelper{parent}
{
    qrCodeView = new QrCodeDialog(parent);
    page = new QWebEnginePage(parent);
    orderPage = new QWebEnginePage(parent);
    config = new JDOrderConfig(parent);


    // Javascript setup
    QFile jsFile;
    // Script to auto-submit order is stored in Qt file system
    // Get jQuery
    QString jQuery;
    jsFile.setFileName(":/scripts/common/jquery-3.7.0.min.js");
    jsFile.open(QFile::ReadOnly);
    jQuery = jsFile.readAll();
    jsFile.close();
    // Get submit order script
    QString orderJs;
    jsFile.setFileName(":/scripts/JDscripts/order.js");
    jsFile.open(QFile::ReadOnly);
    orderJs = jsFile.readAll();
    jsFile.close();
    // Construct QWebEngineScript object
    orderScript.setSourceCode(QString(JD::orderScriptHeader) + jQuery + orderJs);
    orderPage->scripts().insert(orderScript);
    // Page ready signal
    QWebEngineScript signalScript;
    signalScript.setName("signal_emit");
    signalScript.setSourceCode("document.cookie = \"__FastJD__created=1\";");
    signalScript.setInjectionPoint(QWebEngineScript::DocumentCreation);
    signalScript.setWorldId(0);
    page->scripts().insert(signalScript);

    // Regularly refresh page to update log-in status
    keepAliveTimer = new QTimer(this);
    keepAliveTimer->setTimerType(Qt::VeryCoarseTimer);
    keepAliveTimer->setInterval(1200 * 1000);
    keepAliveTimer->setSingleShot(false);

    // Page load control
    connect(page, &QWebEnginePage::loadFinished, this, &JDHelper::_on_page_load);
    connect(page, &QWebEnginePage::urlChanged, this, &JDHelper::_on_url_change);
    connect(page, &QWebEnginePage::loadProgress, this, [this](int p){emit progressUpdated(p);});
    // Order control
    connect(orderPage, &QWebEnginePage::urlChanged, this, &JDHelper::_order_next_step);
    connect(orderPage->profile()->cookieStore(), &QWebEngineCookieStore::cookieAdded,
            this, &JDHelper::_on_cookie_add);
    // Keep-alive timer
    connect(keepAliveTimer, &QTimer::timeout, this, &JDHelper::_reload);
    connect(page, &QWebEnginePage::loadStarted, keepAliveTimer, QOverload<>::of(&QTimer::start));
    connect(orderPage, &QWebEnginePage::loadStarted, keepAliveTimer, QOverload<>::of(&QTimer::start));
    // Log-in QR code display control
    connect(qrCodeView, &QDialog::accepted, this, &JDHelper::log_in);
    connect(this, &JDHelper::loggedIn, qrCodeView, &QDialog::hide);
    // Mode configuration
    connect(config, &QDialog::accepted, this, &JDHelper::_update_manual_config);
}

void JDHelper::buy_item(QString itemId, int itemCnt)
{
    QUrl url(QString(JD::addItemUrl).arg(itemId).arg(itemCnt));
    orderPage->load(url);
}

void JDHelper::_on_page_load()
{
    qDebug() << "Page finished loading";
    QUrl url = page->url();
    if (url.matches(QUrl(JD::loginUrl), JD::domainCompareRules)) {
        qrCodeView->set_source(QString(JD::qrCodeSrc).arg(QDateTime::currentMSecsSinceEpoch()));
    }
    // 抱歉!  您访问的页面失联啦...
    else if (url.matches(QUrl(JD::error2Url), JD::fileCompareRules)) {
        emit imageSrcReady("https://static.360buyimg.com/devfe/error-new/1.0.0/css/i/error_06.png");
    }
    // 亲爱的用户，您刷新过于频繁，请稍后再试，您可以先去首页逛逛，系统将自动为您跳转......
    else if (url.matches(QUrl(JD::error104Url), JD::fileCompareRules)) {
        emit imageSrcReady("https://static.360buyimg.com/devfe/error-new/1.0.0/css/i/error_06.png");
    }
    // Fetch username from homepage
    else if (url.matches(QUrl(JD::homeUrl), JD::domainCompareRules)) {
        page->toHtml([this](const QString &html){analyze_home_page(html);});
    }
    // Not sure if this covers all item urls
    else if (url.toString().contains("item.jd")) {
//        analyze_item_page();
        page->toHtml([this](const QString &html){analyze_item_page(html);});
    }
    else {
        qDebug() << "Page loaded:" << url;
    }
}

void JDHelper::_on_url_change(const QUrl &url)
{
    if (url.matches(QUrl(JD::homeUrl), JD::domainCompareRules)) {
        emit loggedIn(QString("Loading username..."));
    }
    // If at log-in page, show a spinner and wait for QR code
    else if (url.matches(QUrl(JD::loginUrl), JD::fileCompareRules)) {
        qrCodeView->set_spinner();
        qrCodeView->show();
    }
    else {
        qDebug() << "Url changed to" << url;
    }
}

void JDHelper::_order_next_step(const QUrl &url)
{
    // If at cart, go to checkout page
    if (url.matches(QUrl(JD::addItemUrl), JD::domainCompareRules)) {
        orderPage->load(QUrl(JD::checkoutUrl));
    }
    // If at checkout page, do nothing in auto mode (JS will auto submit order)
    else if (url.matches(QUrl(JD::checkoutUrl), JD::fileCompareRules)) {
        if (advancedMode) {
            // Manual mode
            qint64 msecs = QDateTime::currentMSecsSinceEpoch();
            QString url = QString(JD::submitUrl).arg(msecs).arg(uuid);
            QString payload = QString(JD::submitPayload1) + QString(JD::submitPayload2).arg(eid, fp);
            QNetworkRequest request;
            request.setUrl(url);
            request.setRawHeader("Referer", "https://trade.jd.com/");
            request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
            QNetworkReply * postReply = browserPost(request, payload.toLocal8Bit());
            connect(postReply, &QNetworkReply::finished, this, [postReply](){
                qDebug() << "Got reply for post";
                qDebug() << "Status code: " << postReply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
                qDebug() << postReply->url();
                qDebug() << postReply->readAll();
            });
            qDebug() << "Post url: " << request.url();
            qDebug() << "Post data: " << payload;
        }
    }
    // 抱歉!  您访问的页面失联啦...
    else if (url.matches(QUrl(JD::error2Url), JD::fileCompareRules)) {
        emit orderFinished(false);
        // FIXME: only one orderFinished(false) would be emitted if
        // multiple faliures with invalid item id/count happen consecutively,
        // because the url is not chaned after the first failure
    }
    // 亲爱的用户，您刷新过于频繁，请稍后再试，您可以先去首页逛逛，系统将自动为您跳转......
    else if (url.matches(QUrl(JD::error104Url), JD::fileCompareRules)) {
        emit orderFinished(false);
    }
    // Unexpected page
    else {
        qWarning() << "Unexpected page:";
        qWarning() << url;
    }
}

void JDHelper::_reload()
{
    page->triggerAction(QWebEnginePage::Reload);
}

void JDHelper::_update_manual_config()
{
    // 1. Update order mode
    advancedMode = config->manualMode();
    if (advancedMode) {
        // Get required params
        uuid = config->getUuid();
        eid = config->getEid();
        fp = config->getFp();
        // Remove auto-post script
        orderPage->scripts().remove(orderScript);
        qInfo() << "Switched to manual mode. Auto-post disabled.";
    } else if (!orderPage->scripts().contains(orderScript)) {
        orderPage->scripts().insert(orderScript);
        qInfo() << "Switched to auto mode.";
    }
}

void JDHelper::get_item_detail(const QString &itemId)
{
    QUrl url(QString(JD::itemUrl).arg(itemId));
    page->load(url);
    request_item_detail(itemId);
}

void JDHelper::show_config()
{
    config->show();
}

void JDHelper::analyze_home_page(const QString &html)
{
    static const QRegularExpression usernameRegex("<div class=\"user\">[\\s]*<a href=[^<>]+>([^<>]*)");
    QRegularExpressionMatch match;
    match = usernameRegex.match(html);
    if (match.hasMatch()) emit loggedIn(match.captured(1));
}

void JDHelper::analyze_item_page(const QString &html)
{
    // Item name: use title
    static const QRegularExpression nameRegex("name[\\s]*:[\\s]*['\"](.+?)['\"]");
    // Price: from the (unique) "J-p-<skuId>" span class
    static const QRegularExpression priceRegex("<span class=\"price J-p-[0-9]+\">(.+?)</span>");
    // Image: use the zoomed image source because that's unique. May also use data-origin
    static const QRegularExpression imgRegex("<img[^<>]*id=\"spec-img\"[^<>]*data-origin=\"([^\"]+)\"");
    // Stock: from the store-prompt div
    static const QRegularExpression stockRegex("class=\"store-prompt\"[\\s]*>(.+?)</div>");
    // Shop: from the data-seller attribute of any tag
    static const QRegularExpression shopRegex("data-seller=\"([^\"]+)\"[\\s]*data-code");

    QRegularExpressionMatch match;
    match = nameRegex.match(html);
    if (match.hasMatch()) emit itemNameReady(match.captured(1));
    match = priceRegex.match(html);
    if (match.hasMatch()) emit itemPriceReady(match.captured(1));
    match = imgRegex.match(html);
    if (match.hasMatch()) emit imageSrcReady(QString("https:") + match.captured(1));
    match = stockRegex.match(html);
    if (match.hasMatch()) emit itemStatusReady(match.captured(1));
    match = shopRegex.match(html);
    if (match.hasMatch()) emit shopNameReady(match.captured(1));
}

void JDHelper::request_item_detail(const QString &itemId)
{
    QUrl url(QString(JD::itemUrl).arg(itemId));
    QNetworkRequest request;
    request.setUrl(url);
    QNetworkReply *reply = browserGet(request);
    connect(reply, &QNetworkReply::finished, this, [this, reply](){
        QByteArray html = reply->readAll();
        analyze_item_page(html);
        QFile outfile("item_test.html");
        outfile.open(QFile::WriteOnly);
        outfile.write(html);
        outfile.close();
    });
}

void JDHelper::log_in()
{
    page->load(QUrl(JD::homeUrl));
}

QNetworkReply *JDHelper::browserGet(QNetworkRequest &request)
{
    request.setHeader(QNetworkRequest::UserAgentHeader, USER_AGENT);
    request.setRawHeader("sec-ch-ua", SEC_CH_UA);
    request.setRawHeader("sec-ch-ua-mobile", SEC_CH_UA_MOBILE);
    request.setRawHeader("sec-ch-ua-platform", SEC_CH_UA_PLATFORM);
    return accessManager.get(request);
}

QNetworkReply *JDHelper::browserPost(QNetworkRequest &request, const QByteArray &payload)
{
    request.setHeader(QNetworkRequest::UserAgentHeader, USER_AGENT);
    request.setRawHeader("sec-ch-ua", SEC_CH_UA);
    request.setRawHeader("sec-ch-ua-mobile", SEC_CH_UA_MOBILE);
    request.setRawHeader("sec-ch-ua-platform", SEC_CH_UA_PLATFORM);
    return accessManager.post(request, payload);
}

void JDHelper::_on_cookie_add(const QNetworkCookie &cookie)
{
    if (cookie.name().startsWith("__FastJD__")) {
        // These are app-defined cookies
        qDebug() << cookie.name() << ":" << cookie.value();
        if (cookie.name() == QString("__FastJD__status")) {
            if (cookie.value() == QString("1")) {
                emit orderFinished(true);
                // FIXME: program may still report success even if submission fails
            } else {
                emit orderFinished(false);
            }
        }
        if (cookie.name() == QString("__FastJD__ready")) {
            qDebug() << "Document ready";
            emit pageReady();
        }
        orderPage->profile()->cookieStore()->deleteCookie(cookie);
    } else {
        // These are the actual JD cookies
        accessManager.cookieJar()->insertCookie(cookie);

        if (!advancedMode) {
            if (cookie.name() == QString("__jda")) {
                config->setUuid(cookie.value());
            }
        }
    }
}
