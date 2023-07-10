#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>
#include <QTimer>
#include "orderinfo.h"
#include "orderhelper.h"

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
    void unplan_order(qint64 key);
    void unplan_order(QListWidgetItem *item);
    void update_countdown();
    QListWidgetItem * create_list_item(QString time, QString id, int cnt);

private:
    Ui::MainWindow *ui;
    QMap<qint64, OrderInfo*> _plannedOrders;
    OrderHelper *helper;

public slots:
    void log_in();
    void get_item_detail();
    void plan_order();
    void handle_order_result(bool success);
    void set_img_src(const QString &src);
    void manage_order_list(QListWidgetItem *item);
};

#endif // MAINWINDOW_H
