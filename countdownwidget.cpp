#include "countdownwidget.h"
#include "ui_countdownwidget.h"

CountdownWidget::CountdownWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CountdownWidget)
{
    ui->setupUi(this);

    ui->lcdNumber->display(QString("--:--:--.--"));
    connect(&timer, &QTimer::timeout, this, &CountdownWidget::update);
    timer.setInterval(100);
}

CountdownWidget::~CountdownWidget()
{
    delete ui;
}

bool CountdownWidget::getShowMillis() const
{
    return showMillis;
}

void CountdownWidget::setShowMillis(bool newShowMillis)
{
    showMillis = newShowMillis;
}

void CountdownWidget::toggleDisplay(bool on)
{
    on ? start() : stop();
}

QDateTime CountdownWidget::getTarget() const
{
    return target;
}

void CountdownWidget::setTarget(const QDateTime &newTarget)
{
    target = newTarget;
}

void CountdownWidget::start()
{
    timer.start();
}

void CountdownWidget::stop()
{
    timer.stop();
    ui->lcdNumber->display(QString("--:--:--.--"));
}

/**
 * @brief CountdownWidget::update
 *
 * Calculate the gap between current time and target time,
 * then convert the gap to "hh:mm:ss" format and show on UI
 */
void CountdownWidget::update()
{
    if (target.isValid()) {
        qint64 timeDelta = QDateTime::currentDateTime().msecsTo(target);
        int hours = timeDelta / (3600 * 1000);
        if (timeDelta < 0 || hours > 99) {
            ui->lcdNumber->display(QString("--:--:--.--"));
        } else {
            int remaining;
            remaining = timeDelta - (hours * 3600 * 1000);
            int minutes = remaining / (60 * 1000);
            remaining = remaining - (minutes * 60 * 1000);
            int seconds = remaining / 1000;
            int millis = remaining % 1000;
            if (showMillis) {
                ui->lcdNumber->display(
                    QString::asprintf("%2d:%02d:%02d.%02d", hours, minutes, seconds, millis/10));
            } else {
                ui->lcdNumber->display(
                    QString::asprintf("%2d:%02d:%02d.--", hours, minutes, seconds));
            }
        }
    } else {
        ui->lcdNumber->display(QString("--:--:--.--"));
    }
}
