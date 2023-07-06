#ifndef PAGELOADCALLBACK_H
#define PAGELOADCALLBACK_H

#include <QUrl>
#include <QFile>
#include <QWebEnginePage>
#include <QWebEngineScript>
#include <QLineEdit>
#include "./ui_mainwindow.h"
#include "urls.h"

/**
 * @brief The PageLoadCallback class
 * An empty callback class that is the base of all other actions.
 * These actions are intended to be performed when a page starts
 * or finishes loading
 */
class PageLoadCallback
{
public:
    QUrl url;
    PageLoadCallback(QUrl url = QUrl()) : url(url) {}
    virtual ~PageLoadCallback() {}
    virtual void run(QWebEnginePage * page = nullptr, Ui::MainWindow * ui = nullptr) {}
};

class QRCodeCallback : public PageLoadCallback
{
public:
    QRCodeCallback(QUrl url = QUrl(JD::loginUrl)) : PageLoadCallback(url) {}
    virtual ~QRCodeCallback() {}
    virtual void run(QWebEnginePage * page = nullptr, Ui::MainWindow * ui = nullptr) {
        QString html = QString("<img src=\"%1\" style=\"display: block; width: 100%\">").arg(
            QString(JD::qrCodeSrc).arg(QDateTime::currentMSecsSinceEpoch())
            );
        ui->webView->setHtml(html);
    }
};

class LogInCallback : public PageLoadCallback
{
public:
    LogInCallback(QUrl url = QUrl(JD::mainUrl)) : PageLoadCallback(url) {}
    virtual ~LogInCallback() {}
    virtual void run(QWebEnginePage * page = nullptr, Ui::MainWindow * ui = nullptr) {
        qDebug() << "Logged in";
    }
};

class CheckOutCallback : public PageLoadCallback
{
public:
    CheckOutCallback(QUrl url = QUrl(JD::addItemUrl)) : PageLoadCallback(url) {}
    virtual ~CheckOutCallback() {}
    virtual void run(QWebEnginePage * page = nullptr, Ui::MainWindow * ui = nullptr) {
        page->load(QUrl(JD::checkoutUrl));
        qDebug() << "Going to checkout page";
    }
};

class SubmitOrderCallback : public PageLoadCallback
{
public:
    QString jQuery;
    QString order_js;
    SubmitOrderCallback(QUrl url = QUrl(JD::checkoutUrl)) : PageLoadCallback(url) {
        QFile file;
        // Get jQuery
        file.setFileName(":/scripts/common/jquery-3.7.0.min.js");
        file.open(QIODevice::ReadOnly);
        jQuery = file.readAll();
        file.close();
        // Get JD submit_Order code
        file.setFileName(":/scripts/JDscripts/order.js");
        file.open(QIODevice::ReadOnly);
        order_js = file.readAll();
        file.close();
    }
    virtual ~SubmitOrderCallback() {}
    virtual void run(QWebEnginePage * page = nullptr, Ui::MainWindow * ui = nullptr) {
        page->runJavaScript(jQuery + order_js);
        qDebug() << "Submit Order";
    }
};

class ItemDetailCallback : public PageLoadCallback
{
public:
    ItemDetailCallback(QUrl url = QUrl(JD::itemUrl)) : PageLoadCallback(url) {}
    virtual ~ItemDetailCallback() {}
    virtual void run(QWebEnginePage * page = nullptr, Ui::MainWindow * ui = nullptr) {
        page->runJavaScript("document.getElementById('spec-img').src", 0, [ui](const QVariant &v){
            ui->webView->setHtml(
                QString("<img src=\"%1\" style=\"display: block; width: 100%\">").
                arg(v.toString()));
        });
        page->runJavaScript(QString(JD::itemNameSelector), 0, [ui](const QVariant &v) {
            ui->itemNameLabel->setText(v.toString().trimmed());
        });
        page->runJavaScript(QString(JD::itemPriceSelector), 0, [ui](const QVariant &v) {
            ui->priceLabel->setText(v.toString().remove(' ').remove('\n'));
        });
        page->runJavaScript(QString(JD::itemStockSelector), 0, [ui](const QVariant &v) {
            ui->stockLabel->setText(v.toString().trimmed());
        });
        page->runJavaScript(QString(JD::shopNameSelector), 0, [ui](const QVariant &v) {
            ui->shopNameLabel->setText(v.toString().remove(' ').remove('\n'));
        });
    }
};

#endif // PAGELOADCALLBACK_H
