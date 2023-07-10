#ifndef COUNTDOWNWIDGET_H
#define COUNTDOWNWIDGET_H

#include <QWidget>
#include <QTimer>
#include <QDateTime>

namespace Ui {
class CountdownWidget;
}

class CountdownWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CountdownWidget(QWidget *parent = nullptr);
    ~CountdownWidget();

    QDateTime target;
    QTimer timer;
    bool showMillis;

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
