#include "urls.h"
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QThread>
#include <QDateTime>
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

//    this->_page = new QWebEnginePage;
    this->_page = this->ui->webView2->page();
    connect(this->_page, &QWebEnginePage::urlChanged, this, &MainWindow::_on_load_start);
    connect(this->_page, &QWebEnginePage::loadFinished, this, &MainWindow::_on_load_finish);
    connect(this->_page, &QWebEnginePage::loadProgress, this->ui->progressBar, &QProgressBar::setValue);
    connect(this->ui->qrCodeReloadBtn, &QAbstractButton::clicked, this, &MainWindow::log_in);
    connect(this->ui->orderBtn, &QAbstractButton::clicked, this, &MainWindow::buy_item);

    // Debug connections
    connect(this->_page, &QWebEnginePage::loadStarted, this, &MainWindow::__debug_load_start);
    connect(this->_page, &QWebEnginePage::urlChanged, this, &MainWindow::__debug_url_changed);
//    connect(this->_page, &QWebEnginePage::visibleChanged, this, &MainWindow::__debug_visible);
//    connect(this->_page, &QWebEnginePage::loadProgress, this, &MainWindow::__debug_progress);

    // Debug scripts"window.alert(\"Boo~\")"

    QWebEngineScript test_script;
    test_script.setSourceCode(QString(JD::orderScriptHeader) + QString(R"(window.alert("Boo~");)"));
    qDebug() << "Script name: " << test_script.name();
    qDebug() << "script run at: " << test_script.injectionPoint();
    qDebug() << "Script source code: " << test_script.sourceCode();
    _page->scripts().insert(test_script);

    log_in();
//    this->_page->load(QUrl(QString("https://www.example.com")));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete _page;
}

void MainWindow::log_in()
{
    // Clear any remaining (expired) actions
    _loadFinishCallbacks.clear();
    _loadStartCallbacks.clear();
    this->ui->webView->setHtml("");
    this->_page->load(QUrl(JD::loginUrl));
}

void MainWindow::add_to_cart(QString itemID, int count)
{
    qDebug() << "Adding item" << itemID << "to cart";
    _page->load(QUrl(QString(JD::addItemUrl).arg(itemID).arg(count)));
}

void MainWindow::buy_item()
{
    CheckOutCallback * checkout = new CheckOutCallback;
//    SubmitOrderCallback * submit = new SubmitOrderCallback;
    QString itemID = this->ui->itemIDEdit->text();
    // Clear any remaining (expired) actions
    _loadFinishCallbacks.clear();
    _loadStartCallbacks.clear();
    // TODO:
    // create a script containing
    //      script header (JD namespace)
    //      jQuery (from file)
    //      JD submit order code (from file)
    // and add it to the script collection of _page
    // Also don't forget to remove the original submit callback
    // Enqueue follow-up actions after item is added
    this->_loadStartCallbacks.enqueue(checkout);
//    this->_loadFinishCallbacks.enqueue(submit);
    add_to_cart(itemID);
}

void MainWindow::clear_actions()
{
    // Clear any remaining (expired) actions
    _loadFinishCallbacks.clear();
    _loadStartCallbacks.clear();
    _page->scripts().clear();
}

void MainWindow::_on_load_start(const QUrl &url)
{
    PageLoadCallback * callback;
    qDebug() << "Started loading page " << _page->title();
    qDebug() << url;

    if (!_loadStartCallbacks.empty()) {
        callback = _loadStartCallbacks.head();
        if (url.matches(callback->url, JD::urlCompareRules) || callback->url.isEmpty()) {
            _loadStartCallbacks.dequeue();
            callback->run(this->_page, this->ui);
            delete callback;
        } else {
            qDebug() << "URL mismatch";
            qDebug() << "LHS : " << url;
            qDebug() << "RHS : " << callback->url;
        }
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
            _loadFinishCallbacks.dequeue();
            callback->run(this->_page, this->ui);
            delete callback;
        } else {
            qDebug() << "URL mismatch";
            qDebug() << "LHS : " << currentUrl.adjusted(JD::urlCompareRules);
            qDebug() << "RHS : " << callback->url.adjusted(JD::urlCompareRules);
        }
    }
    // If at log-in page, always qr code and display in App
    if (currentUrl.matches(QUrl(JD::loginUrl), JD::urlCompareRules)) {
        QRCodeCallback qrCodeRun;
        qrCodeRun.run(this->_page, this->ui);
    } else {
        qDebug() << "URL mismatch";
        qDebug() << "LHS : " << currentUrl.adjusted(JD::urlCompareRules);
        qDebug() << "RHS : " << QUrl(JD::loginUrl).adjusted(JD::urlCompareRules);
    }
    // If at home page, clear all pending tasks
    if (currentUrl.matches(QUrl(JD::homeUrl), JD::urlCompareRules)) {
        _loadFinishCallbacks.clear();
        _loadStartCallbacks.clear();
    } else {
        qDebug() << "URL mismatch";
        qDebug() << "LHS : " << currentUrl.adjusted(JD::urlCompareRules);
        qDebug() << "RHS : " << QUrl(JD::homeUrl).adjusted(JD::urlCompareRules);
    }
}
