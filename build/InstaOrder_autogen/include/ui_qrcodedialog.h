/********************************************************************************
** Form generated from reading UI file 'qrcodedialog.ui'
**
** Created by: Qt User Interface Compiler version 6.5.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QRCODEDIALOG_H
#define UI_QRCODEDIALOG_H

#include <QtCore/QVariant>
#include <QtWebEngineWidgets/QWebEngineView>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_QrCodeDialog
{
public:
    QVBoxLayout *verticalLayout;
    QWebEngineView *widget;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *QrCodeDialog)
    {
        if (QrCodeDialog->objectName().isEmpty())
            QrCodeDialog->setObjectName("QrCodeDialog");
        QrCodeDialog->resize(380, 479);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(QrCodeDialog->sizePolicy().hasHeightForWidth());
        QrCodeDialog->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(QrCodeDialog);
        verticalLayout->setSpacing(10);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(10, 10, 10, 10);
        widget = new QWebEngineView(QrCodeDialog);
        widget->setObjectName("widget");
        sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy);
        widget->setMinimumSize(QSize(360, 420));

        verticalLayout->addWidget(widget);

        buttonBox = new QDialogButtonBox(QrCodeDialog);
        buttonBox->setObjectName("buttonBox");
        QSizePolicy sizePolicy1(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(buttonBox->sizePolicy().hasHeightForWidth());
        buttonBox->setSizePolicy(sizePolicy1);
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Retry);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(QrCodeDialog);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, QrCodeDialog, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, QrCodeDialog, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(QrCodeDialog);
    } // setupUi

    void retranslateUi(QDialog *QrCodeDialog)
    {
        QrCodeDialog->setWindowTitle(QCoreApplication::translate("QrCodeDialog", "\350\257\267\346\211\253\347\240\201\347\231\273\345\275\225", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QrCodeDialog: public Ui_QrCodeDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QRCODEDIALOG_H
