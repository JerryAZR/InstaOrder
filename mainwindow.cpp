#include "urls.h"
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QThread>
#include <QDateTime>
#include <QTimer>
#include <QWebEngineCookieStore>
#include <QWebEngineProfile>
#include <QWebEngineScriptCollection>
#include <QProgressBar>
#include <QAbstractButton>
#include <QFile>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Member initialization
        _page = new QWebEnginePage(this);
//    _page = ui->webView2->page();
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

    // Debug connections
//    connect(ui->dateTimeEdit, &QDateTimeEdit::dateTimeChanged, this, [](QDateTime time){qDebug() << time;});
    //    connect(_page, &QWebEnginePage::loadStarted, this, &MainWindow::__debug_load_start);
    //    connect(_page, &QWebEnginePage::urlChanged, this, &MainWindow::__debug_url_changed);
    //    connect(_page, &QWebEnginePage::visibleChanged, this, &MainWindow::__debug_visible);
    //    connect(_page, &QWebEnginePage::loadProgress, this, &MainWindow::__debug_progress);
    //    connect(_webcpp, &WebCpp::documentReady, this, &MainWindow::__debug_doc_ready);
    //    connect(_webcpp, &WebCpp::documentStart, this, &MainWindow::__debug_doc_start);

    // First task
    log_in();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::log_in()
{
    // Clear any remaining (expired) actions
    clear_actions();
    ui->webView->setHtml("");
    _page->load(QUrl(JD::loginUrl));
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
    qint64 time = ui->dateTimeEdit->dateTime().toMSecsSinceEpoch() + 1000;
    OrderInfo *info = new OrderInfo(itemID, 1, time);
    prepare_order(info);
}

void MainWindow::prepare_order(OrderInfo *info)
{
    CheckOutCallback * checkout = new CheckOutCallback;
    // Clear any remaining (expired) actions
    clear_actions();
    // Order submit is handled with script injection,
    // so checkout (getOrderInfo) is the only action to be queued
    _loadStartCallbacks.enqueue(checkout);
    // Check whether the order should be placed now or later
    qint64 targetTime = info->orderTimeMSec;
    qint64 now = QDateTime::currentMSecsSinceEpoch();
    if (now >= targetTime) {
        // Order should be placed immediately
        place_order(info->itemId, info->itemCount);
    } else {
        // Set-up a timer to add item to cart at specified time
        qint64 delay = targetTime - now;
        QTimer::singleShot(delay, Qt::PreciseTimer, info, [this, info](){
            this->place_order(info->itemId, info->itemCount);
        });
    }
}

void MainWindow::place_order(QString itemID, int itemCount)
{
    _page->load(QUrl(QString(JD::addItemUrl).arg(itemID).arg(itemCount)));
}

void MainWindow::clear_actions()
{
    // Clear any remaining (expired) actions
    _loadFinishCallbacks.clear();
    _loadStartCallbacks.clear();
}

void MainWindow::_on_load_start(const QUrl &url)
{
    PageLoadCallback * callback;
    qDebug() << "Started loading page " << _page->title();
    qDebug() << url;

    if (!_loadStartCallbacks.empty()) {
        callback = _loadStartCallbacks.head();
        if (url.matches(callback->url, JD::urlCompareRules) || callback->url.isEmpty()) {
            callback->run(_page, ui);
            _loadStartCallbacks.dequeue();
            delete callback;
        }
        //        else {
        //            qDebug() << "URL mismatch";
        //            qDebug() << "LHS : " << url;
        //            qDebug() << "RHS : " << callback->url;
        //        }
    }
}

void MainWindow::_on_load_finish()
{
    PageLoadCallback * callback;
    QUrl currentUrl = _page->url();
    // Always-active actions
    qDebug() << "Finished loading page";
    qDebug() << currentUrl;

    // One-time actions from callback queue
    if (!_loadFinishCallbacks.empty()) {
        callback = _loadFinishCallbacks.head();
        if (currentUrl.matches(callback->url, JD::urlCompareRules) || callback->url.isEmpty()) {
            callback->run(_page, ui);
            _loadFinishCallbacks.dequeue();
            delete callback;
        }
        //        else {
        //            qDebug() << "URL mismatch";
        //            qDebug() << "LHS : " << currentUrl.adjusted(JD::urlCompareRules);
        //            qDebug() << "RHS : " << callback->url.adjusted(JD::urlCompareRules);
        //        }
    }
    // If at log-in page, always qr code and display in App
    if (currentUrl.matches(QUrl(JD::loginUrl), JD::urlCompareRules)) {
        QRCodeCallback qrCodeRun;
        qrCodeRun.run(_page, ui);
    }
    //    else {
    //        qDebug() << "URL mismatch";
    //        qDebug() << "LHS : " << currentUrl.adjusted(JD::urlCompareRules);
    //        qDebug() << "RHS : " << QUrl(JD::loginUrl).adjusted(JD::urlCompareRules);
    //    }
    // If at home page, clear all pending tasks
    if (currentUrl.matches(QUrl(JD::homeUrl), JD::urlCompareRules)) {
        _loadFinishCallbacks.clear();
        _loadStartCallbacks.clear();
    }
    //    else {
    //        qDebug() << "URL mismatch";
    //        qDebug() << "LHS : " << currentUrl.adjusted(JD::urlCompareRules);
    //        qDebug() << "RHS : " << QUrl(JD::homeUrl).adjusted(JD::urlCompareRules);
    //    }
}
