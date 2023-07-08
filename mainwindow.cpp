#include "urls.h"
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QThread>
#include <QDateTime>
#include <QTimer>
#include <QWebEngineCookieStore>
#include <QWebEngineProfile>
#include <QWebEngineScriptCollection>
#include <QNetworkReply>
#include <QProgressBar>
#include <QAbstractButton>
#include <QListWidget>
#include <QMessageBox>
#include <QFile>
#include <QStandardPaths>
#include <QRegularExpression>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Member initialization
    _page = new QWebEnginePage(this);
    //    qDebug() << QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    //    qDebug() << "cookie store path:" << _page->profile()->persistentStoragePath();
    //    qDebug() << "Policy is off-the record" << _page->profile()->isOffTheRecord();
    _keepAliveTimer = new QTimer(this);
    _keepAliveTimer->setTimerType(Qt::VeryCoarseTimer);
    _keepAliveTimer->setInterval(1200 * 1000);
    _keepAliveTimer->setSingleShot(false);

    _accessManager = new QNetworkAccessManager(this);
    _cookieJar = _accessManager->cookieJar();
    _userAgent = _page->profile()->httpUserAgent();

    // UI initialization
    QTime now = QTime::currentTime();
    QDateTime target = QDateTime(QDate::currentDate(), QTime(now.hour(), now.minute()));
    ui->dateTimeEdit->setDateTime(target);

    // Javascript setup
    QFile jsFile;
    // Script to submit order is stored in Qt file system
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
    _orderScript.setSourceCode(QString(JD::orderScriptHeader) + jQuery + orderJs);
    _page->scripts().insert(_orderScript);

    // Signal connections after all members are initialized
    connect(_page, &QWebEnginePage::urlChanged, this, &MainWindow::_on_load_start);
    connect(_page, &QWebEnginePage::loadFinished, this, &MainWindow::_on_load_finish);
    connect(_page, &QWebEnginePage::loadProgress, ui->progressBar, &QProgressBar::setValue);
    connect(ui->qrCodeReloadBtn, &QAbstractButton::clicked, this, &MainWindow::reload);
    connect(ui->orderBtn, &QAbstractButton::clicked, this, &MainWindow::plan_order);
    connect(ui->getDetailBtn, &QAbstractButton::clicked, this, &MainWindow::get_item_detail);
    connect(ui->loginBtn, &QAbstractButton::clicked, this, &MainWindow::log_in);
    connect(_page->profile()->cookieStore(), &QWebEngineCookieStore::cookieAdded, this, &MainWindow::_on_cookie_add);
    connect(_keepAliveTimer, &QTimer::timeout, this, &MainWindow::reload);
    connect(_page, &QWebEnginePage::loadStarted, _keepAliveTimer, [this](){_keepAliveTimer->start();});

    // Debug connections
    //    connect(ui->dateTimeEdit, &QDateTimeEdit::dateTimeChanged, this, [](QDateTime time){qDebug() << time;});
    //    connect(_page, &QWebEnginePage::loadStarted, this, &MainWindow::__debug_load_start);
    //    connect(_page, &QWebEnginePage::urlChanged, this, &MainWindow::__debug_url_changed);
    //    connect(_page, &QWebEnginePage::visibleChanged, this, &MainWindow::__debug_visible);
    //    connect(_page, &QWebEnginePage::loadProgress, this, &MainWindow::__debug_progress);
    //    connect(_webcpp, &WebCpp::documentReady, this, &MainWindow::__debug_doc_ready);
    //    connect(_webcpp, &WebCpp::documentStart, this, &MainWindow::__debug_doc_start);


    // First task
//    log_in();
    connect(&helper, &OrderHelper::qrCodeReady, this, [this](QPixmap * img){
        qDebug() << "Trying to set img";
        ui->qrCodeLabel->setPixmap(*img);
    });

    helper.log_in();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::log_in()
{
    // Clear any remaining (expired) actions
    ui->webView->setHtml("");
    _page->load(QUrl(JD::homeUrl));
}

void MainWindow::get_item_detail()
{
    QString itemId = ui->itemIDEdit->text();
    _page->load(QUrl(QString(JD::itemUrl).arg(itemId)));
}

void MainWindow::load_item_detail()
{
    _page->runJavaScript("document.getElementById('spec-img').src", 0, [this](const QVariant &v){
        ui->webView->setHtml(
            QString("<img src=\"%1\" style=\"display: block; width: 100%\">").
            arg(v.toString()));
    });
    _page->runJavaScript(QString(JD::itemNameSelector), 0, [this](const QVariant &v) {
        ui->itemNameLabel->setText(v.toString().trimmed());
    });
    _page->runJavaScript(QString(JD::itemPriceSelector), 0, [this](const QVariant &v) {
        ui->priceLabel->setText(v.toString().remove(' ').remove('\n'));
    });
    _page->runJavaScript(QString(JD::itemStockSelector), 0, [this](const QVariant &v) {
        ui->stockLabel->setText(v.toString().trimmed());
    });
    _page->runJavaScript(QString(JD::shopNameSelector), 0, [this](const QVariant &v) {
        ui->shopNameLabel->setText(v.toString().remove(' ').remove('\n'));
    });
}

void MainWindow::reload()
{
    _page->triggerAction(QWebEnginePage::Reload);
}

void MainWindow::plan_order()
{
    QString itemID = ui->itemIDEdit->text();
    // TODO: If sufficient time remains, add order to the planned queue
    // Otherwise, prepare it immediately;
    qint64 time = ui->dateTimeEdit->dateTime().toMSecsSinceEpoch();
    int delay = ui->delaySpinBox->value();
    int itemCnt = ui->itemCntSpinBox->value();
    OrderInfo *info = new OrderInfo(itemID, itemCnt, time + delay);
    qint64 timeDelta = time - QDateTime::currentMSecsSinceEpoch();
    if (_plannedOrders.contains(time)) {
        // TODO: Ask if user want to replace
        delete info;
        return;
    }
    _plannedOrders.insert(time, info);
    if (timeDelta > 5000) {
        // More than 5 seconds remaining. Schedule the preparation task to execute later
        QTimer::singleShot(timeDelta, Qt::VeryCoarseTimer, info, [this, time](){
            prepare_order(time);
        });
    } else {
        // Less than 5 seconds remaining. Start the preparation immediately;
        prepare_order(time);
    }
    // Create a label for the scheduled order
    info->listItem = create_list_item(ui->dateTimeEdit->text(), itemID, itemCnt);
    ui->listWidget->addItem(info->listItem);
    //    ui->tmpLabel->setText(QString("Order %1 planned.").arg(itemID));
}

void MainWindow::prepare_order(qint64 orderTime)
{
    // Reset keep-alive timer so we don't get interrupted
    _keepAliveTimer->start();
    // Check whether the order should be placed now or later
    OrderInfo * info = _plannedOrders.take(orderTime);
    qint64 targetTime = info->orderTimeMSec;
    qint64 now = QDateTime::currentMSecsSinceEpoch();
    if (now >= targetTime) {
        // Order should be placed immediately
        place_order(info->itemId, info->itemCount);
        delete info;
    } else {
        // Set-up a timer to add item to cart at specified time
        qint64 delay = targetTime - now;
        QTimer::singleShot(delay, Qt::PreciseTimer, this, [this, info](){
            place_order(info->itemId, info->itemCount);
            delete info;
        });
    }
}

void MainWindow::place_order(QString itemID, int itemCount)
{
    helper.buy_item(itemID, itemCount);
}

void MainWindow::request_checkout()
{
    QNetworkRequest request((QUrl(JD::checkoutUrl)));
    request.setHeader(QNetworkRequest::UserAgentHeader, _userAgent);
    request.setRawHeader("Referer", "https://cart.jd.com/");
    QNetworkReply * reply = _accessManager->get(request);
    connect(reply, &QNetworkReply::finished, this, [this, reply](){
        if (reply->url().matches(QUrl(JD::checkoutUrl), JD::fileCompareRules)) {
            request_submit_order(reply);
        } else {
            qDebug() << "Did not get checkout page. Got this url instead:";
            qDebug() << "reply url:" << reply->url();
            reply->close();
            reply->deleteLater();
        }
    });
}

void MainWindow::request_submit_order(QNetworkReply *reply)
{
    static const QRegularExpression regex("<input[^<>]+id=\"([^<>\"]+)\"[^<>]+value=\"([^<>\"]+)\"[^<>]*>");
    qDebug() << "one step ahead!";
    QByteArray data = reply->readAll();
    QRegularExpressionMatchIterator iter = regex.globalMatch(data);
    while (iter.hasNext()) {
        QRegularExpressionMatch match = iter.next();
        qDebug() << match.captured(1) << match.captured(2);
    }
    QFile checkoutPage;
    checkoutPage.setFileName("checkout.html");
    checkoutPage.open(QFile::WriteOnly);
    checkoutPage.write(data);
    checkoutPage.close();

    reply->close();
    reply->deleteLater();
}

QListWidgetItem *MainWindow::create_list_item(QString time, QString id, int cnt)
{
    QString itemLabel = QString("[%1] %2 * %3").arg(time, id).arg(cnt);
    QListWidgetItem * listItem = new QListWidgetItem(itemLabel);
    return listItem;
}

void MainWindow::_on_load_start(const QUrl &url)
{
    // If at cart, go to checkout page
    if (url.matches(QUrl(JD::addItemUrl), JD::domainCompareRules)) {
        _page->load(QUrl(JD::checkoutUrl));
    }
}

void MainWindow::_on_load_finish()
{
    QUrl currentUrl = _page->url();

    // If at log-in page, always qr code and display in App
    if (currentUrl.matches(QUrl(JD::loginUrl), JD::domainCompareRules)) {
        QString html;
        html = QString("<img src=\"%1\" style=\"display: block; width: 100%\">").arg(
            QString(JD::qrCodeSrc).arg(QDateTime::currentMSecsSinceEpoch())
            );
        ui->webView->setHtml(html);
    }

    // If at item page, get item detail
    if (currentUrl.matches(QUrl(JD::itemUrl), JD::domainCompareRules)) {
        load_item_detail();
    }
    // If at error page, report
    if (currentUrl.matches(QUrl(JD::error2Url), JD::fileCompareRules)) {
        qCritical() << "Cannot add item to cart.";
        QMessageBox::information(this, "Error", currentUrl.toDisplayString());
    }
    if (currentUrl.matches(QUrl(JD::error104Url), JD::fileCompareRules)) {
        qCritical() << "Failed to get checkout page.";
        QMessageBox::information(this, "Error", currentUrl.toDisplayString());
    }

    // Always try to update username
    _page->runJavaScript("document.getElementsByClassName('nickname')[0].textContent", 0, [this](const QVariant &v){
        this->ui->nicknameLabel->setText(v.toString());
    });
}

void MainWindow::_on_cookie_add(const QNetworkCookie &cookie)
{
    if (cookie.name().startsWith("__FastJD__")) {
        qDebug() << cookie.name() << ":" << cookie.value();
    } else {
        // Sync cookie between webengine and network manager
        _cookieJar->insertCookie(cookie);
    }
    if (cookie.name() == QString("__FastJD__status")) {
        if (cookie.value() == QString("1")) {
            QMessageBox::information(this, "", QString("下单成功"));
        } else {
            QMessageBox::information(this, "", QString("下单失败"));
        }
    }
}
