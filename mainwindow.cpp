#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QThread>
#include <QDateTime>
#include <QNetworkAccessManager>
#include <QProgressBar>
#include <QAbstractButton>
#include <QListWidget>
#include <QListWidgetItem>
#include <QMessageBox>
#include <QMenu>
#include <QCursor>
#include "jdhelper.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Member initialization
    helper = new JDHelper(this);

    // UI initialization
    QTime now = QTime::currentTime();
    QDateTime target = QDateTime(QDate::currentDate(), QTime(now.hour(), now.minute()));
    ui->dateTimeEdit->setDateTime(target);
    // Disable order submission until user is logged in
    ui->orderBtn->setDisabled(true);
    // Configure item id field to accept only numbers
    // For some reason setting a validator disables paste (not desired)
//    ui->itemIdEdit->setValidator(new QIntValidator(this));

    // Signal connections after all members are initialized
    // Button signals
    connect(ui->orderBtn, &QAbstractButton::clicked, this, &MainWindow::plan_order);
    connect(ui->getDetailBtn, &QAbstractButton::clicked, this, &MainWindow::get_item_detail);
    connect(ui->loginBtn, &QAbstractButton::clicked, this, &MainWindow::log_in);
    connect(ui->cfgButton, &QAbstractButton::clicked, helper, &OrderHelper::show_config);
    // Planned order management
    connect(ui->listWidget, &QListWidget::itemClicked, this, &MainWindow::manage_order_list);
    // Order helper signals
    connect(helper, &OrderHelper::progressUpdated, ui->progressBar, &QProgressBar::setValue);
    connect(helper, &OrderHelper::orderFinished, this, &MainWindow::handle_order_result);
    connect(helper, &OrderHelper::itemNameReady, ui->itemNameLabel, &QLabel::setText);
    connect(helper, &OrderHelper::itemPriceReady, ui->priceLabel, &QLabel::setText);
    connect(helper, &OrderHelper::itemStatusReady, ui->stockLabel, &QLabel::setText);
    connect(helper, &OrderHelper::shopNameReady, ui->shopNameLabel, &QLabel::setText);
    connect(helper, &OrderHelper::imageSrcReady, this, &MainWindow::set_img_src);
    connect(helper, &OrderHelper::loggedIn, ui->nicknameLabel, &QLabel::setText);
    connect(helper, &OrderHelper::loggedIn, this, [this](){ui->orderBtn->setDisabled(false);});
    // Countdown timer
    connect(ui->millisSelect, &QCheckBox::clicked, ui->countdown, &CountdownWidget::setShowMillis);
    connect(ui->countdownSelect, &QCheckBox::clicked, ui->countdown, &CountdownWidget::toggleDisplay);
    // First task
    log_in();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::log_in()
{
    helper->log_in();
}

void MainWindow::get_item_detail()
{
    // Clear item info fields
    ui->itemNameLabel->clear();
    ui->shopNameLabel->clear();
    ui->stockLabel->clear();
    ui->priceLabel->clear();
    ui->imgLabel->clear();
    QString itemId = ui->itemIdEdit->text();
    helper->get_item_detail(itemId);
}

/**
 * @brief MainWindow::plan_order
 *
 * Add the order to a QMap if sufficient time remains.
 * Orders in the map can be deleted.
 */
void MainWindow::plan_order()
{
    QString itemId = ui->itemIdEdit->text();
    if (itemId.isEmpty()) return;
    // If sufficient time remains, add order to the planned queue
    // Otherwise, prepare it immediately;
    qint64 time = ui->dateTimeEdit->dateTime().toMSecsSinceEpoch();
    int delay = ui->delaySpinBox->value();
    int itemCnt = ui->itemCntSpinBox->value();
    OrderInfo *info = new OrderInfo(itemId, itemCnt, time + delay);
    qint64 timeDelta = time - QDateTime::currentMSecsSinceEpoch();
    if (_plannedOrders.contains(time)) {
        // TODO: Ask if user want to replace
        delete info;
        return;
    }
    _plannedOrders.insert(time, info);
    if (timeDelta > 3000) {
        // More than 3 seconds remaining. Schedule the preparation task to execute later
        QTimer::singleShot(timeDelta, Qt::VeryCoarseTimer, info, [this, time](){
            prepare_order(time);
        });
    } else {
        // Less than 3 seconds remaining. Start the preparation immediately;
        prepare_order(time);
    }
    // Create a label for the scheduled order
    info->listItem = create_list_item(ui->dateTimeEdit->text(), itemId, itemCnt);
    ui->listWidget->addItem(info->listItem);
    update_countdown();
}

void MainWindow::handle_order_result(bool success)
{
    if (success) {
        QMessageBox::information(this, "Success", QString("下单成功 ") + QString::fromUtf8("\xF0\x9F\x98\x8F"));
    } else {
        QMessageBox::information(this, "Failed", QString("下单失败 ") + QString::fromUtf8("\xF0\x9F\x98\xA5"));
    }
}

void MainWindow::set_img_src(const QString &src)
{
    static QNetworkAccessManager manager;
    QNetworkRequest request;
    request.setUrl(QUrl(src));
    QNetworkReply *reply = manager.get(request);
    connect(reply, &QNetworkReply::finished, this, [this, reply](){
        QPixmap img;
        img.loadFromData(reply->readAll());
        if (img.isNull()) {
            qDebug() << "Got null pixmap from" << reply->url();
        } else {
            ui->imgLabel->setPixmap(img.scaled(ui->imgLabel->size(), Qt::KeepAspectRatio));
        }
    });
}

/**
 * @brief MainWindow::manage_order_list
 * @param item
 *
 * Show a context menu when an item (order entry) is clicked.
 */
void MainWindow::manage_order_list(QListWidgetItem *item)
{
    qDebug() << "Item" << item << "clicked";
    QMenu menu(this);
    QAction delAction(QString("Delete orders"), &menu);
    connect(&delAction, &QAction::triggered, this, [this, item](){
        qDebug() << "Deleting" << item->text();
        unplan_order(item);
    });
    menu.addAction(&delAction);
    menu.exec(QCursor::pos());
}

/**
 * @brief MainWindow::prepare_order
 * @param orderTime
 *
 * Schedule the order (tagged with order time) to be submitted on time.
 * If specified time has passed, submit the order immediately.
 */
void MainWindow::prepare_order(qint64 orderTime)
{
    // Check whether the order should be placed now or later
    OrderInfo * info = _plannedOrders.value(orderTime);
    qint64 targetTime = info->orderTimeMSec;
    qint64 now = QDateTime::currentMSecsSinceEpoch();
    if (now >= targetTime) {
        // Order should be placed immediately
        place_order(info->itemId, info->itemCount);
        unplan_order(orderTime);
    } else {
        // Set-up a timer to add item to cart at specified time
        qint64 delay = targetTime - now;
        QTimer::singleShot(delay, Qt::PreciseTimer, this, [this, info, orderTime](){
            place_order(info->itemId, info->itemCount);
            unplan_order(orderTime);
        });
    }
}

void MainWindow::place_order(QString itemID, int itemCount)
{
    qInfo() << "Buy item" << itemID << "x" << itemCount;
    helper->buy_item(itemID, itemCount);
}

void MainWindow::unplan_order(qint64 key)
{
    if (_plannedOrders.contains(key)) {
        _plannedOrders.take(key)->deleteLater();
        update_countdown();
    } else {
        qWarning() << "Target" << key << "does not seem to be a planned order";
    }
}

void MainWindow::unplan_order(QListWidgetItem *item)
{
    QString plan = item->text();
    QString time = plan.first(plan.indexOf(']')).remove(0, plan.indexOf('[')+1);
    QDateTime datetime = QDateTime::fromString(time, QString("yyyy/M/d hh:mm"));
    if (datetime.isValid()) {
        unplan_order(datetime.toMSecsSinceEpoch());
    } else {
        qDebug() << "Got an invalid DateTime string: " << time;
    }
}

void MainWindow::update_countdown()
{
    if (_plannedOrders.isEmpty()) {
        ui->countdown->stop();
    } else {
        qint64 millis = _plannedOrders.constBegin().key();
        ui->countdown->setTarget(QDateTime::fromMSecsSinceEpoch(millis));
        ui->countdown->start();
    }
}

QListWidgetItem *MainWindow::create_list_item(QString time, QString id, int cnt)
{
    QString itemLabel = QString("[%1] %2 * %3").arg(time, id).arg(cnt);
    QListWidgetItem * listItem = new QListWidgetItem(itemLabel);
    return listItem;
}
