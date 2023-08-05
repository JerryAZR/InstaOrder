#include "jdhelper.h"
#include "urls.h"
#include <QNetworkCookieJar>
#include <QNetworkCookie>
#include <QWebEngineProfile>
#include <QWebEngineCookieStore>
#include <QWebEngineScriptCollection>
#include <QDialog>
#include <QDateTime>
#include <QFile>
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>

JDHelper::JDHelper(QWidget *parent)
    : OrderHelper{parent}
{
    qrCodeView = new QrCodeDialog(parent);
//    page = new QWebEnginePage(parent);
    page = qrCodeView->get_page();
    orderPage = new QWebEnginePage(parent);
    config = new JDOrderConfig(parent);
    perfTimer.invalidate();

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
    // Page creation signal
    QWebEngineScript signalScript;
    signalScript.setName("start_signal_emit");
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
    connect(this, &JDHelper::pageCreated, this, &JDHelper::_on_url_change);
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
    connect(config, &QDialog::finished, this, &JDHelper::_update_manual_config);
}

/**
 * @brief JDHelper::buy_item
 * @param itemId
 * @param itemCnt
 *
 * If in advanced mode, send an HTTP GET request to add selected item to cart,
 * then set-up a callback to checkout after JD server replies.
 *
 * If in auto mode, load the link that adds the selected item to cart.
 * The following steps are handled elsewhere:
 * - checkout is performed in function _order_next_step
 * - submission is handled by the orderScript added to page script collection.
 */
void JDHelper::buy_item(QString itemId, int itemCnt)
{
    perfTimer.start();
    if (advancedMode) {
        // Use QNetworkRequest-based method with user-defined params
        if (rushMode) {
            qDebug() << "Rush order";
            request_add_item(itemId, itemCnt, false, false);
            QTimer::singleShot(reqInterval, this, [this](){request_checkout(true);});
//            QTimer::singleShot(200, this, [this](){request_submit_order();});
        } else {
            request_add_item(itemId, itemCnt, true, true);
        }
    } else {
        QUrl url(QString(JD::addItemUrl).arg(itemId).arg(itemCnt));
        orderPage->load(url);
    }
}

/**
 * @brief JDHelper::_on_page_load
 *
 * Preforms various actions on the loaded page, depending on its url.
 */
void JDHelper::_on_page_load()
{
    qDebug() << "Page finished loading";
    QUrl url = page->url();
    if (url.matches(QUrl(JD::loginUrl), JD::domainCompareRules)) {
//        qrCodeView->set_source(QString(JD::qrCodeSrc).arg(QDateTime::currentMSecsSinceEpoch()));
//        qrCodeView->set_page(page);
        page->runJavaScript("document.getElementsByClassName('login-form')[0].scrollIntoView();", [this](const QVariant &v){
            qrCodeView->show();
        });
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
        page->toHtml([this](const QString &html){analyze_item_page(html);});
    }
    else {
        qDebug() << "Page loaded:" << url;
    }

    // Get eid
    page->runJavaScript("jdtRiskContext.deviceInfo.jsToken", 0, [this](const QVariant &v){
        if(!v.toString().isEmpty()) {
            config->setEid(v.toString());
        }
    });
    // Get fp
    page->runJavaScript("jdtRiskContext.deviceInfo.fp", 0, [this](const QVariant &v){
        if(!v.toString().isEmpty()) {
            config->setFp(v.toString());
        }
    });
}

/**
 * @brief JDHelper::_on_url_change
 * @param url
 *
 * Preforms various actions on the current page (before it is fully loaded).
 * Action depends on its url.
 */
void JDHelper::_on_url_change()
{
    QUrl url = page->url();
    if (url.matches(QUrl(JD::homeUrl), JD::domainCompareRules)) {
        emit loggedIn(QString("Loading username..."));
    }
    // If at log-in page, show a spinner and wait for QR code
    else if (url.matches(QUrl(JD::loginUrl), JD::fileCompareRules)) {
        // TODO: Add a spinner
//        qrCodeView->set_page(dummyPage);
//        qrCodeView->set_spinner();
//        qrCodeView->show();
    }
    else {
        qDebug() << "Url changed to" << url;
    }
}

/**
 * @brief JDHelper::_order_next_step
 * @param url
 *
 * Similar to _on_url_change, but only handles order-related stuff
 * Specifically, it loads the checkout page once the item is added to cart
 * and reports error (order failure) if an error page is seen.
 */
void JDHelper::_order_next_step(const QUrl &url)
{
    // If at cart, go to checkout page
    if (url.matches(QUrl(JD::addItemUrl), JD::domainCompareRules)) {
        orderPage->load(QUrl(JD::checkoutUrl));
    }
    // If at checkout page, do nothing in auto mode (JS will auto submit order)
    else if (url.matches(QUrl(JD::checkoutUrl), JD::fileCompareRules)) {}
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

/**
 * @brief JDHelper::_update_manual_config
 * @param result
 *
 * Update parameters used in manual mode with user input.
 */
void JDHelper::_update_manual_config(int result)
{
    if (result == QDialog::Accepted) {
        // Update order mode
        advancedMode = config->manualMode();
        if (advancedMode) {
            // Get required params
            uuid = config->getUuid();
            eid = config->getEid();
            fp = config->getFp();
            qInfo() << "Switched to manual mode. Auto-post disabled.";
        } else {
            qInfo() << "Switched to auto mode.";
        }

        rushMode = config->rushMode();
        reqInterval = config->getInterval();
        if (rushMode) qDebug() << "Enabled rush mode";
        else qDebug() << "Disabled rush mode";
        // TODO: update request interval
    } else {
        // Restore mode selection
        config->setManualMode(advancedMode);
        config->setRushMode(rushMode);
        config->setInterval(reqInterval);
    }
}

/**
 * @brief JDHelper::get_item_detail
 * @param itemId
 *
 * Get item name and image with a raw HTTP GET request (fast),
 * then wait for QWebEngine to load the full item page to get the other info.
 */
void JDHelper::get_item_detail(const QString &itemId)
{
    QUrl url(QString(JD::itemUrl).arg(itemId));
    page->load(url);
    request_item_detail(itemId);
}

/**
 * @brief JDHelper::show_config
 *
 * Show the configuration window.
 */
void JDHelper::show_config()
{
    config->show();
}

/**
 * @brief JDHelper::analyze_home_page
 * @param html
 *
 * Extract username with QRegularExpression from home.jd.com html document.
 */
void JDHelper::analyze_home_page(const QString &html)
{
    static const QRegularExpression usernameRegex("<div class=\"user\">[\\s]*<a href=[^<>]+>([^<>]*)");
    QRegularExpressionMatch match;
    match = usernameRegex.match(html);
    if (match.hasMatch()) emit loggedIn(match.captured(1));
}

/**
 * @brief JDHelper::analyze_item_page
 * @param html
 *
 * Get item name, price, image, stock status, and shop name from item page.
 */
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
    perfTimer.start();
    QNetworkReply *reply = browserGet(request);
    connect(reply, &QNetworkReply::finished, this, [this, reply](){
        config->setInterval(perfTimer.elapsed() / 2);
        QByteArray html = reply->readAll();
        analyze_item_page(html);
        perfTimer.invalidate();
    });
}

/**
 * @brief JDHelper::request_add_item
 * @param itemId
 * @param itemCnt
 * @param ckeckout  Whether to auto-checkout after item added to cart.
 * @param submit    Whether to auto-submit after checkout.
 *
 * Items are added to cart by submitting a GET request with item ID and
 * quantity as payload.
 */
void JDHelper::request_add_item(QString itemId, int itemCnt, bool ckeckout, bool submit)
{
    QNetworkRequest request(QUrl(QString(JD::addItemUrl).arg(itemId).arg(itemCnt)));
    request.setRawHeader("Referer", "https://item.jd.com/");
    QNetworkReply * reply = browserGet(request);
    connect(reply, &QNetworkReply::finished, this, [this, reply, ckeckout, submit](){
        if (reply->url().matches(QUrl(JD::addItemUrl), JD::domainCompareRules)) {
            qDebug() << "Item added to cart";
            if (ckeckout) request_checkout(submit);
        } else {
            qWarning() << "Item not added to cart. Got this url instead:";
            qWarning() << "reply url:" << reply->url();
        }
        reply->close();
        reply->deleteLater();
    });
}

/**
 * @brief JDHelper::request_checkout
 * @param submit    Whether to auto-submit after checkout.
 *
 * Checkout with an HTTP GET request and set up a callback to submit order
 * after JD server respondes.
 */
void JDHelper::request_checkout(bool submit)
{
    QNetworkRequest request((QUrl(JD::checkoutUrl)));
    request.setRawHeader("Referer", "https://cart.jd.com/");
    QNetworkReply * reply = browserGet(request);
    connect(reply, &QNetworkReply::finished, this, [this, reply, submit](){
        if (reply->url().matches(QUrl(JD::checkoutUrl), JD::fileCompareRules)) {
            if (submit) request_submit_order();
        } else {
            qWarning() << "Did not get checkout page. Got this url instead:";
            qWarning() << "reply url:" << reply->url();
        }
        reply->close();
        reply->deleteLater();
    });
}

/**
 * @brief JDHelper::request_submit_order
 *
 * Construct an order submission POST request with data provided by user ansd
 * set-up a callback to report order status.
 */
void JDHelper::request_submit_order()
{
    // Manual mode
    qint64 msecs = QDateTime::currentMSecsSinceEpoch();
    QString url = QString(JD::submitUrl).arg(msecs).arg(uuid);
    QString payload = QString(JD::submitPayload1) + QString(JD::submitPayload2).arg(eid, fp);
    QNetworkRequest request;
    request.setUrl(url);
    request.setRawHeader("Referer", "https://trade.jd.com/");
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    QNetworkReply * postReply = browserPost(request, payload.toLocal8Bit());
    connect(postReply, &QNetworkReply::finished, this, [this, postReply](){
        QJsonDocument body;
        qInfo() << "Got reply for post";
        qInfo() << "Status code: " << postReply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
        qInfo() << postReply->url();
        body = QJsonDocument::fromJson(postReply->readAll());
        qInfo() << "Response body:" << body;
        handle_return_code(body.object().value("resultCode").toInt(-1));
    });
    qInfo() << "Post url: " << request.url();
    qInfo() << "Post data: " << payload;
    qInfo() << "Order submitted in" << perfTimer.elapsed() << "milliseconds";
}

/**
 * @brief JDHelper::log_in
 *
 * Log-in by loading home.jd.com.
 */
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

void JDHelper::handle_return_code(int code)
{
    qInfo() << "Order finisned in" << perfTimer.elapsed() << "milliseconds";
    perfTimer.invalidate();
    if (code == 0) {
        emit orderFinished(true);
    } else {
        emit orderFinished(false);
        qWarning() << "Order failed with status code" << code;
    }
}

/**
 * @brief JDHelper::_on_cookie_add
 * @param cookie
 *
 * Copy cookies in QWebEngine to QNetworkAccessManager
 */
void JDHelper::_on_cookie_add(const QNetworkCookie &cookie)
{
    if (cookie.name().startsWith("__FastJD__")) {
        // These are app-defined cookies
        qDebug() << cookie.name() << ":" << cookie.value();
        if (cookie.name() == QString("__FastJD__status")) {
            bool success;
            int code = cookie.value().toInt(&success);
            if (!success) code = -1;
            handle_return_code(code);
        }
        else if (cookie.name() == QString("__FastJD__ready")) {
            qDebug() << "Document ready";
            emit pageReady();
        }
        else if (cookie.name() == QString("__FastJD__created")) {
            qDebug() << "Document created";
            emit pageCreated();
        }
        else if (cookie.name() == QString("__FastJD__params")) {
            qInfo() << "Order submitted in" << perfTimer.elapsed() << "milliseconds";
        }
        else if (cookie.name() == QString("__FastJD__eid")) {
            if (!advancedMode) config->setEid(cookie.value());
        }
        else if (cookie.name() == QString("__FastJD__fp")) {
            if (!advancedMode) config->setFp(cookie.value());
        }
        orderPage->profile()->cookieStore()->deleteCookie(cookie);
    } else {
        // These are the actual JD cookies
        accessManager.cookieJar()->insertCookie(cookie);
        if (cookie.name() == QString("__jda")) {
            if (!advancedMode) config->setUuid(cookie.value());
        }
    }
}
