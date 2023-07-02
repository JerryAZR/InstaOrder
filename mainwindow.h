#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWebEnginePage>
#include <QWebEngineLoadingInfo>
#include <QNetworkCookie>
#include <QQueue>
#include "pageLoadCallbacks.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QWebEnginePage *_page;
    QQueue<PageLoadCallback*> _loadStartCallbacks;
    QQueue<PageLoadCallback*> _loadFinishCallbacks;

public slots:
    void log_in();
    void add_to_cart(QString itemID, int count = 1);
    void buy_item();
    void clear_actions();

private slots:
    void _on_load_start(const QUrl &url);
    void _on_load_finish();

    void __debug_load_start() {qDebug() << "load_start emmited for " << _page->url();}
    void __debug_url_changed(const QUrl &url) {qDebug() << "url changed to " << url;}
    void __debug_visible(bool visible) {qDebug() << "Visibility changed to " << visible;}
    void __debug_progress(int prog) {qDebug() << "Loading progress" << prog;}
};

#endif // MAINWINDOW_H
