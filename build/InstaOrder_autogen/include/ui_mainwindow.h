/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.5.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "countdownwidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_6;
    QLabel *nicknameLabel;
    QPushButton *loginBtn;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QLineEdit *itemIdEdit;
    QPushButton *getDetailBtn;
    QLabel *label_2;
    QSpinBox *itemCntSpinBox;
    QProgressBar *progressBar;
    QFormLayout *formLayout;
    QLabel *label_7;
    QLabel *itemNameLabel;
    QLabel *label_9;
    QLabel *priceLabel;
    QLabel *label_8;
    QLabel *shopNameLabel;
    QLabel *label_10;
    QLabel *stockLabel;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_3;
    QDateTimeEdit *dateTimeEdit;
    QLabel *label_4;
    QSpinBox *delaySpinBox;
    QLabel *label_5;
    QHBoxLayout *horizontalLayout;
    QPushButton *orderBtn;
    QToolButton *cfgButton;
    QHBoxLayout *horizontalLayout_6;
    QCheckBox *countdownSelect;
    QCheckBox *millisSelect;
    CountdownWidget *countdown;
    QVBoxLayout *verticalLayout;
    QLabel *imgLabel;
    QListWidget *listWidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(643, 474);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        horizontalLayout_2 = new QHBoxLayout(centralwidget);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName("label_6");
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy);

        horizontalLayout_5->addWidget(label_6);

        nicknameLabel = new QLabel(centralwidget);
        nicknameLabel->setObjectName("nicknameLabel");
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(nicknameLabel->sizePolicy().hasHeightForWidth());
        nicknameLabel->setSizePolicy(sizePolicy1);

        horizontalLayout_5->addWidget(nicknameLabel);

        loginBtn = new QPushButton(centralwidget);
        loginBtn->setObjectName("loginBtn");

        horizontalLayout_5->addWidget(loginBtn);


        verticalLayout_2->addLayout(horizontalLayout_5);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy2);

        horizontalLayout_3->addWidget(label);

        itemIdEdit = new QLineEdit(centralwidget);
        itemIdEdit->setObjectName("itemIdEdit");
        itemIdEdit->setMinimumSize(QSize(128, 0));

        horizontalLayout_3->addWidget(itemIdEdit);

        getDetailBtn = new QPushButton(centralwidget);
        getDetailBtn->setObjectName("getDetailBtn");

        horizontalLayout_3->addWidget(getDetailBtn);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        sizePolicy2.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy2);

        horizontalLayout_3->addWidget(label_2);

        itemCntSpinBox = new QSpinBox(centralwidget);
        itemCntSpinBox->setObjectName("itemCntSpinBox");
        itemCntSpinBox->setMinimum(1);
        itemCntSpinBox->setValue(1);

        horizontalLayout_3->addWidget(itemCntSpinBox);


        verticalLayout_2->addLayout(horizontalLayout_3);

        progressBar = new QProgressBar(centralwidget);
        progressBar->setObjectName("progressBar");
        sizePolicy.setHeightForWidth(progressBar->sizePolicy().hasHeightForWidth());
        progressBar->setSizePolicy(sizePolicy);
        progressBar->setMinimumSize(QSize(20, 2));
        progressBar->setMaximumSize(QSize(16777215, 4));
        progressBar->setValue(0);
        progressBar->setTextVisible(false);
        progressBar->setOrientation(Qt::Horizontal);
        progressBar->setInvertedAppearance(false);
        progressBar->setFormat(QString::fromUtf8("%p%"));

        verticalLayout_2->addWidget(progressBar);

        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        formLayout->setFieldGrowthPolicy(QFormLayout::ExpandingFieldsGrow);
        label_7 = new QLabel(centralwidget);
        label_7->setObjectName("label_7");
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(label_7->sizePolicy().hasHeightForWidth());
        label_7->setSizePolicy(sizePolicy3);

        formLayout->setWidget(0, QFormLayout::LabelRole, label_7);

        itemNameLabel = new QLabel(centralwidget);
        itemNameLabel->setObjectName("itemNameLabel");
        sizePolicy1.setHeightForWidth(itemNameLabel->sizePolicy().hasHeightForWidth());
        itemNameLabel->setSizePolicy(sizePolicy1);
        itemNameLabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        itemNameLabel->setWordWrap(true);

        formLayout->setWidget(0, QFormLayout::FieldRole, itemNameLabel);

        label_9 = new QLabel(centralwidget);
        label_9->setObjectName("label_9");
        sizePolicy3.setHeightForWidth(label_9->sizePolicy().hasHeightForWidth());
        label_9->setSizePolicy(sizePolicy3);

        formLayout->setWidget(2, QFormLayout::LabelRole, label_9);

        priceLabel = new QLabel(centralwidget);
        priceLabel->setObjectName("priceLabel");
        sizePolicy1.setHeightForWidth(priceLabel->sizePolicy().hasHeightForWidth());
        priceLabel->setSizePolicy(sizePolicy1);

        formLayout->setWidget(2, QFormLayout::FieldRole, priceLabel);

        label_8 = new QLabel(centralwidget);
        label_8->setObjectName("label_8");
        sizePolicy3.setHeightForWidth(label_8->sizePolicy().hasHeightForWidth());
        label_8->setSizePolicy(sizePolicy3);

        formLayout->setWidget(3, QFormLayout::LabelRole, label_8);

        shopNameLabel = new QLabel(centralwidget);
        shopNameLabel->setObjectName("shopNameLabel");
        sizePolicy1.setHeightForWidth(shopNameLabel->sizePolicy().hasHeightForWidth());
        shopNameLabel->setSizePolicy(sizePolicy1);
        shopNameLabel->setWordWrap(true);

        formLayout->setWidget(3, QFormLayout::FieldRole, shopNameLabel);

        label_10 = new QLabel(centralwidget);
        label_10->setObjectName("label_10");

        formLayout->setWidget(1, QFormLayout::LabelRole, label_10);

        stockLabel = new QLabel(centralwidget);
        stockLabel->setObjectName("stockLabel");
        sizePolicy1.setHeightForWidth(stockLabel->sizePolicy().hasHeightForWidth());
        stockLabel->setSizePolicy(sizePolicy1);
        stockLabel->setWordWrap(true);

        formLayout->setWidget(1, QFormLayout::FieldRole, stockLabel);


        verticalLayout_2->addLayout(formLayout);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");
        sizePolicy2.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy2);

        horizontalLayout_4->addWidget(label_3);

        dateTimeEdit = new QDateTimeEdit(centralwidget);
        dateTimeEdit->setObjectName("dateTimeEdit");
        QSizePolicy sizePolicy4(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(dateTimeEdit->sizePolicy().hasHeightForWidth());
        dateTimeEdit->setSizePolicy(sizePolicy4);
        dateTimeEdit->setCalendarPopup(true);

        horizontalLayout_4->addWidget(dateTimeEdit);

        label_4 = new QLabel(centralwidget);
        label_4->setObjectName("label_4");
        sizePolicy2.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy2);

        horizontalLayout_4->addWidget(label_4);

        delaySpinBox = new QSpinBox(centralwidget);
        delaySpinBox->setObjectName("delaySpinBox");
        delaySpinBox->setMinimumSize(QSize(64, 0));
        delaySpinBox->setMaximum(5000);
        delaySpinBox->setSingleStep(100);
        delaySpinBox->setValue(0);

        horizontalLayout_4->addWidget(delaySpinBox);

        label_5 = new QLabel(centralwidget);
        label_5->setObjectName("label_5");
        sizePolicy2.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy2);

        horizontalLayout_4->addWidget(label_5);


        verticalLayout_2->addLayout(horizontalLayout_4);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        orderBtn = new QPushButton(centralwidget);
        orderBtn->setObjectName("orderBtn");

        horizontalLayout->addWidget(orderBtn);

        cfgButton = new QToolButton(centralwidget);
        cfgButton->setObjectName("cfgButton");

        horizontalLayout->addWidget(cfgButton);


        verticalLayout_2->addLayout(horizontalLayout);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        countdownSelect = new QCheckBox(centralwidget);
        countdownSelect->setObjectName("countdownSelect");
        countdownSelect->setChecked(true);
        countdownSelect->setTristate(false);

        horizontalLayout_6->addWidget(countdownSelect);

        millisSelect = new QCheckBox(centralwidget);
        millisSelect->setObjectName("millisSelect");
        millisSelect->setChecked(false);

        horizontalLayout_6->addWidget(millisSelect);


        verticalLayout_2->addLayout(horizontalLayout_6);

        countdown = new CountdownWidget(centralwidget);
        countdown->setObjectName("countdown");
        QSizePolicy sizePolicy5(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(countdown->sizePolicy().hasHeightForWidth());
        countdown->setSizePolicy(sizePolicy5);
        countdown->setMinimumSize(QSize(0, 20));

        verticalLayout_2->addWidget(countdown);


        horizontalLayout_2->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        imgLabel = new QLabel(centralwidget);
        imgLabel->setObjectName("imgLabel");
        QSizePolicy sizePolicy6(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(imgLabel->sizePolicy().hasHeightForWidth());
        imgLabel->setSizePolicy(sizePolicy6);
        imgLabel->setMinimumSize(QSize(200, 200));

        verticalLayout->addWidget(imgLabel);

        listWidget = new QListWidget(centralwidget);
        listWidget->setObjectName("listWidget");
        QSizePolicy sizePolicy7(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);
        sizePolicy7.setHorizontalStretch(0);
        sizePolicy7.setVerticalStretch(0);
        sizePolicy7.setHeightForWidth(listWidget->sizePolicy().hasHeightForWidth());
        listWidget->setSizePolicy(sizePolicy7);
        listWidget->setMaximumSize(QSize(200, 16777215));

        verticalLayout->addWidget(listWidget);


        horizontalLayout_2->addLayout(verticalLayout);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 643, 26));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Insta-Order", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "\345\275\223\345\211\215\347\224\250\346\210\267\357\274\232", nullptr));
        nicknameLabel->setText(QString());
        loginBtn->setText(QCoreApplication::translate("MainWindow", "\346\211\253\347\240\201\347\231\273\345\275\225", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\345\225\206\345\223\201\347\274\226\345\217\267", nullptr));
        itemIdEdit->setText(QString());
        getDetailBtn->setText(QCoreApplication::translate("MainWindow", "\350\216\267\345\217\226\345\225\206\345\223\201\344\277\241\346\201\257", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\346\225\260\351\207\217", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "\345\225\206\345\223\201\345\220\215\357\274\232", nullptr));
        itemNameLabel->setText(QString());
        label_9->setText(QCoreApplication::translate("MainWindow", "\344\273\267\346\240\274\357\274\232", nullptr));
        priceLabel->setText(QString());
        label_8->setText(QCoreApplication::translate("MainWindow", "\345\272\227\351\223\272\357\274\232", nullptr));
        shopNameLabel->setText(QString());
        label_10->setText(QCoreApplication::translate("MainWindow", "\347\212\266\346\200\201\357\274\232", nullptr));
        stockLabel->setText(QString());
        label_3->setText(QCoreApplication::translate("MainWindow", "\344\270\213\345\215\225\346\227\266\351\227\264", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "\345\273\266\350\277\237\344\270\213\345\215\225", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "ms", nullptr));
        orderBtn->setText(QCoreApplication::translate("MainWindow", "\345\207\206\345\244\207\344\270\213\345\215\225", nullptr));
        cfgButton->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        countdownSelect->setText(QCoreApplication::translate("MainWindow", "\346\230\276\347\244\272\345\200\222\350\256\241\346\227\266", nullptr));
        millisSelect->setText(QCoreApplication::translate("MainWindow", "\346\230\276\347\244\272\346\257\253\347\247\222", nullptr));
        imgLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
