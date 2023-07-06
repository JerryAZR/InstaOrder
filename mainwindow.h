#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWebEnginePage>
#include <QWebEngineScript>
#include <QNetworkCookie>
#include <QMap>
#include <QTimer>
#include "orderinfo.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void load_item_detail();
    void prepare_order(qint64 orderTime);
    void place_order(QString itemID, int itemCount);
    QListWidgetItem * create_list_item(QString time, QString id, int cnt);

private:
    Ui::MainWindow *ui;
    QWebEnginePage *_page;
    QWebEngineScript _orderScript;
    QMap<qint64, OrderInfo*> _plannedOrders;
    QTimer *_keepAliveTimer;

public slots:
    void log_in();
    void get_item_detail();
    void reload();
    void plan_order();

private slots:
    void _on_load_start(const QUrl &url);
    void _on_load_finish();
    void _on_cookie_add(const QNetworkCookie &cookie);

    void __debug_load_start() {qDebug() << "load_start emmited for " << _page->url();}
    void __debug_url_changed(const QUrl &url) {qDebug() << "url changed to " << url;}
    void __debug_visible(bool visible) {qDebug() << "Visibility changed to " << visible;}
    void __debug_progress(int prog) {qDebug() << "Loading progress" << prog;}
    void __debug_doc_start() {qDebug() << "[JS] Document creation";}
    void __debug_doc_ready() {qDebug() << "[JS] Document ready";}
};

#endif // MAINWINDOW_H
