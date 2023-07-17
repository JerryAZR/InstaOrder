#ifndef COUNTDOWNWIDGET_H
#define COUNTDOWNWIDGET_H

#include <QWidget>
#include <QTimer>
#include <QDateTime>

namespace Ui {
class CountdownWidget;
}

/**
 * @brief The CountdownWidget class
 *
 * Display a countdown timer that targets a QDateTime in the future
 */
class CountdownWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CountdownWidget(QWidget *parent = nullptr);
    ~CountdownWidget();

    QDateTime target;   // The countdown target
    QTimer timer;       // The timer that updates the countdown periodically
    bool showMillis;    // Select whether to show milliseconds or not

    QDateTime getTarget() const;

    bool getShowMillis() const;

public slots:
    void setTarget(const QDateTime &newTarget);
    void setShowMillis(bool newShowMillis);
    void toggleDisplay(bool on);
    void start();
    void stop();
    void update();

private:
    Ui::CountdownWidget *ui;
};

#endif // COUNTDOWNWIDGET_H
