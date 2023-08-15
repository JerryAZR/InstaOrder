/********************************************************************************
** Form generated from reading UI file 'jdorderconfig.ui'
**
** Created by: Qt User Interface Compiler version 6.5.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_JDORDERCONFIG_H
#define UI_JDORDERCONFIG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_JDOrderConfig
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout;
    QRadioButton *autoModeSel;
    QRadioButton *advModeSel;
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *uuidEdit;
    QLabel *label_2;
    QLineEdit *eidEdit;
    QLabel *label_3;
    QLineEdit *fpEdit;
    QCheckBox *rushMode;
    QLabel *label_4;
    QSpinBox *reqInterval;
    QLabel *label_5;
    QSpacerItem *verticalSpacer;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *JDOrderConfig)
    {
        if (JDOrderConfig->objectName().isEmpty())
            JDOrderConfig->setObjectName("JDOrderConfig");
        JDOrderConfig->resize(400, 329);
        JDOrderConfig->setMinimumSize(QSize(400, 0));
        verticalLayout = new QVBoxLayout(JDOrderConfig);
        verticalLayout->setObjectName("verticalLayout");
        groupBox = new QGroupBox(JDOrderConfig);
        groupBox->setObjectName("groupBox");
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy);
        groupBox->setFlat(false);
        groupBox->setCheckable(false);
        horizontalLayout = new QHBoxLayout(groupBox);
        horizontalLayout->setObjectName("horizontalLayout");
        autoModeSel = new QRadioButton(groupBox);
        autoModeSel->setObjectName("autoModeSel");
        autoModeSel->setChecked(true);

        horizontalLayout->addWidget(autoModeSel);

        advModeSel = new QRadioButton(groupBox);
        advModeSel->setObjectName("advModeSel");

        horizontalLayout->addWidget(advModeSel);


        verticalLayout->addWidget(groupBox);

        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        formLayout->setLabelAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label = new QLabel(JDOrderConfig);
        label->setObjectName("label");
        QSizePolicy sizePolicy1(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        uuidEdit = new QLineEdit(JDOrderConfig);
        uuidEdit->setObjectName("uuidEdit");

        formLayout->setWidget(0, QFormLayout::FieldRole, uuidEdit);

        label_2 = new QLabel(JDOrderConfig);
        label_2->setObjectName("label_2");
        sizePolicy1.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy1);

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        eidEdit = new QLineEdit(JDOrderConfig);
        eidEdit->setObjectName("eidEdit");

        formLayout->setWidget(1, QFormLayout::FieldRole, eidEdit);

        label_3 = new QLabel(JDOrderConfig);
        label_3->setObjectName("label_3");
        sizePolicy1.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy1);
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout->setWidget(2, QFormLayout::LabelRole, label_3);

        fpEdit = new QLineEdit(JDOrderConfig);
        fpEdit->setObjectName("fpEdit");

        formLayout->setWidget(2, QFormLayout::FieldRole, fpEdit);

        rushMode = new QCheckBox(JDOrderConfig);
        rushMode->setObjectName("rushMode");

        formLayout->setWidget(3, QFormLayout::LabelRole, rushMode);

        label_4 = new QLabel(JDOrderConfig);
        label_4->setObjectName("label_4");

        formLayout->setWidget(4, QFormLayout::LabelRole, label_4);

        reqInterval = new QSpinBox(JDOrderConfig);
        reqInterval->setObjectName("reqInterval");
        reqInterval->setReadOnly(false);
        reqInterval->setMinimum(1);
        reqInterval->setMaximum(20000);
        reqInterval->setSingleStep(20);
        reqInterval->setValue(200);

        formLayout->setWidget(4, QFormLayout::FieldRole, reqInterval);

        label_5 = new QLabel(JDOrderConfig);
        label_5->setObjectName("label_5");

        formLayout->setWidget(3, QFormLayout::FieldRole, label_5);


        verticalLayout->addLayout(formLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        buttonBox = new QDialogButtonBox(JDOrderConfig);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(JDOrderConfig);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, JDOrderConfig, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, JDOrderConfig, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(JDOrderConfig);
    } // setupUi

    void retranslateUi(QDialog *JDOrderConfig)
    {
        JDOrderConfig->setWindowTitle(QCoreApplication::translate("JDOrderConfig", "Dialog", nullptr));
        groupBox->setTitle(QCoreApplication::translate("JDOrderConfig", "\344\270\213\345\215\225\346\250\241\345\274\217", nullptr));
        autoModeSel->setText(QCoreApplication::translate("JDOrderConfig", "\350\207\252\345\212\250", nullptr));
        advModeSel->setText(QCoreApplication::translate("JDOrderConfig", "\351\253\230\347\272\247", nullptr));
        label->setText(QCoreApplication::translate("JDOrderConfig", "uuid/__jda:", nullptr));
        uuidEdit->setText(QCoreApplication::translate("JDOrderConfig", "undefined", nullptr));
        label_2->setText(QCoreApplication::translate("JDOrderConfig", "eid:", nullptr));
        label_3->setText(QCoreApplication::translate("JDOrderConfig", "fp:", nullptr));
        rushMode->setText(QCoreApplication::translate("JDOrderConfig", "\346\236\201\351\200\237\346\250\241\345\274\217", nullptr));
        label_4->setText(QCoreApplication::translate("JDOrderConfig", "\350\257\267\346\261\202\351\227\264\351\232\224", nullptr));
        reqInterval->setSuffix(QCoreApplication::translate("JDOrderConfig", " ms", nullptr));
        label_5->setText(QCoreApplication::translate("JDOrderConfig", "\351\234\200\351\205\215\345\220\210\351\253\230\347\272\247\346\250\241\345\274\217\344\275\277\347\224\250", nullptr));
    } // retranslateUi

};

namespace Ui {
    class JDOrderConfig: public Ui_JDOrderConfig {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_JDORDERCONFIG_H
