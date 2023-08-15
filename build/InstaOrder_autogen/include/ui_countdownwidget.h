/********************************************************************************
** Form generated from reading UI file 'countdownwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.5.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COUNTDOWNWIDGET_H
#define UI_COUNTDOWNWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CountdownWidget
{
public:
    QHBoxLayout *horizontalLayout;
    QLCDNumber *lcdNumber;

    void setupUi(QWidget *CountdownWidget)
    {
        if (CountdownWidget->objectName().isEmpty())
            CountdownWidget->setObjectName("CountdownWidget");
        CountdownWidget->resize(400, 300);
        horizontalLayout = new QHBoxLayout(CountdownWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        lcdNumber = new QLCDNumber(CountdownWidget);
        lcdNumber->setObjectName("lcdNumber");
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lcdNumber->sizePolicy().hasHeightForWidth());
        lcdNumber->setSizePolicy(sizePolicy);
        lcdNumber->setSmallDecimalPoint(false);
        lcdNumber->setDigitCount(11);
        lcdNumber->setProperty("value", QVariant(0.000000000000000));
        lcdNumber->setProperty("intValue", QVariant(0));

        horizontalLayout->addWidget(lcdNumber);


        retranslateUi(CountdownWidget);

        QMetaObject::connectSlotsByName(CountdownWidget);
    } // setupUi

    void retranslateUi(QWidget *CountdownWidget)
    {
        CountdownWidget->setWindowTitle(QCoreApplication::translate("CountdownWidget", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CountdownWidget: public Ui_CountdownWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COUNTDOWNWIDGET_H
