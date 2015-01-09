/********************************************************************************
** Form generated from reading UI file 'versionform.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VERSIONFORM_H
#define UI_VERSIONFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_versionForm
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QVBoxLayout *verticalLayout_2;
    QLabel *deviceLabel;
    QLCDNumber *chanLcdNumber;
    QLabel *descLabel;
    QLabel *date_time_label;

    void setupUi(QWidget *versionForm)
    {
        if (versionForm->objectName().isEmpty())
            versionForm->setObjectName(QStringLiteral("versionForm"));
        versionForm->resize(232, 144);
        gridLayout = new QGridLayout(versionForm);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(versionForm);
        label->setObjectName(QStringLiteral("label"));
        QFont font;
        font.setFamily(QStringLiteral("Courier New"));
        label->setFont(font);

        verticalLayout->addWidget(label);

        label_2 = new QLabel(versionForm);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setFont(font);

        verticalLayout->addWidget(label_2);

        label_3 = new QLabel(versionForm);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setFont(font);

        verticalLayout->addWidget(label_3);

        label_4 = new QLabel(versionForm);
        label_4->setObjectName(QStringLiteral("label_4"));

        verticalLayout->addWidget(label_4);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        deviceLabel = new QLabel(versionForm);
        deviceLabel->setObjectName(QStringLiteral("deviceLabel"));
        deviceLabel->setFont(font);

        verticalLayout_2->addWidget(deviceLabel);

        chanLcdNumber = new QLCDNumber(versionForm);
        chanLcdNumber->setObjectName(QStringLiteral("chanLcdNumber"));
        QFont font1;
        font1.setFamily(QStringLiteral("Courier New"));
        font1.setPointSize(24);
        font1.setBold(true);
        font1.setWeight(75);
        chanLcdNumber->setFont(font1);
        chanLcdNumber->setSmallDecimalPoint(false);
        chanLcdNumber->setDigitCount(3);
        chanLcdNumber->setMode(QLCDNumber::Dec);

        verticalLayout_2->addWidget(chanLcdNumber);

        descLabel = new QLabel(versionForm);
        descLabel->setObjectName(QStringLiteral("descLabel"));
        descLabel->setFont(font);

        verticalLayout_2->addWidget(descLabel);

        date_time_label = new QLabel(versionForm);
        date_time_label->setObjectName(QStringLiteral("date_time_label"));

        verticalLayout_2->addWidget(date_time_label);


        horizontalLayout->addLayout(verticalLayout_2);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);


        retranslateUi(versionForm);

        QMetaObject::connectSlotsByName(versionForm);
    } // setupUi

    void retranslateUi(QWidget *versionForm)
    {
        versionForm->setWindowTitle(QApplication::translate("versionForm", "Version info", 0));
        label->setText(QApplication::translate("versionForm", "Device", 0));
        label_2->setText(QApplication::translate("versionForm", "Channels", 0));
        label_3->setText(QApplication::translate("versionForm", "Description", 0));
        label_4->setText(QApplication::translate("versionForm", "Created", 0));
        deviceLabel->setText(QString());
        descLabel->setText(QString());
        date_time_label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class versionForm: public Ui_versionForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VERSIONFORM_H
