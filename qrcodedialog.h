#ifndef QRCODEDIALOG_H
#define QRCODEDIALOG_H

#include <QDialog>
#include <QWebEnginePage>

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
    QWebEnginePage *get_page();
    void set_page(QWebEnginePage *page);

private:
    Ui::QrCodeDialog *ui;
};

#endif // QRCODEDIALOG_H
