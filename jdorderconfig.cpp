#include "jdorderconfig.h"
#include "ui_jdorderconfig.h"

JDOrderConfig::JDOrderConfig(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::JDOrderConfig)
{
    ui->setupUi(this);
}

JDOrderConfig::~JDOrderConfig()
{
    delete ui;
}

QString JDOrderConfig::getUuid() const
{
    return ui->uuidEdit->text();
}

QString JDOrderConfig::getEid() const
{
    return ui->eidEdit->text();
}

QString JDOrderConfig::getFp() const
{
    return ui->fpEdit->text();
}

bool JDOrderConfig::manualMode() const
{
    return ui->advModeSel->isChecked();
}

void JDOrderConfig::setUuid(const QString &newUuid)
{
    ui->uuidEdit->setText(newUuid);
}

void JDOrderConfig::setEid(const QString &newEid)
{
    ui->eidEdit->setText(newEid);
}

void JDOrderConfig::setFp(const QString &newFp)
{
    ui->fpEdit->setText(newFp);
}

void JDOrderConfig::setManualMode(bool manual)
{
    ui->advModeSel->setChecked(manual);
    ui->autoModeSel->setChecked(!manual);
}
