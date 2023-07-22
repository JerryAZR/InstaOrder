#ifndef JDORDERCONFIG_H
#define JDORDERCONFIG_H

#include <QDialog>

namespace Ui {
class JDOrderConfig;
}

class JDOrderConfig : public QDialog
{
    Q_OBJECT

public:
    explicit JDOrderConfig(QWidget *parent = nullptr);
    ~JDOrderConfig();

    QString getUuid() const;
    QString getEid() const;
    QString getFp() const;
    bool manualMode() const;
    bool rushMode() const;
    int getInterval() const;

    void setUuid(const QString &newUuid);
    void setEid(const QString &newEid);
    void setFp(const QString &newFp);
    void setManualMode(bool manual);
    void setRushMode(bool rush);
    void setInterval(int interval);

private:
    Ui::JDOrderConfig *ui;
};

#endif // JDORDERCONFIG_H
