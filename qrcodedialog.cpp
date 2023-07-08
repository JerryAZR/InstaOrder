#include "qrcodedialog.h"
#include "ui_qrcodedialog.h"

QrCodeDialog::QrCodeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QrCodeDialog)
{
    ui->setupUi(this);
}

QrCodeDialog::~QrCodeDialog()
{
    delete ui;
}

void QrCodeDialog::set_source(const QString &src)
{
    QString html;
    html = QString("<img src=\"%1\" style=\"display: block; width: 100%\">").arg(src);
    ui->widget->setHtml(html);
}

void QrCodeDialog::set_spinner()
{
    set_source("https://icons8.com/preloaders/preloaders/35/Fading%20lines.gif");
}
