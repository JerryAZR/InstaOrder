#ifndef QRCODEDIALOG_H
#define QRCODEDIALOG_H

#include <QDialog>

namespace Ui {
class QrCodeDialog;
}

class QrCodeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QrCodeDialog(QWidget *parent = nullptr);
    ~QrCodeDialog();
    void set_source(const QString &src);
    void set_spinner();

private:
    Ui::QrCodeDialog *ui;
};

#endif // QRCODEDIALOG_H
