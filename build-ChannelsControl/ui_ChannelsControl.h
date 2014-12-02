/********************************************************************************
** Form generated from reading UI file 'ChannelsControl.ui'
**
** Created by: Qt User Interface Compiler version 5.1.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHANNELSCONTROL_H
#define UI_CHANNELSCONTROL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_Channels
{
public:
    QGridLayout *gridLayout;
    QTableWidget *tableWidget;

    void setupUi(QDialog *Channels)
    {
        if (Channels->objectName().isEmpty())
            Channels->setObjectName(QStringLiteral("Channels"));
        Channels->resize(1066, 558);
        gridLayout = new QGridLayout(Channels);
        gridLayout->setSpacing(5);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);
        gridLayout->setContentsMargins(5, 5, 5, 5);
        tableWidget = new QTableWidget(Channels);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        QFont font;
        font.setFamily(QStringLiteral("Courier New"));
        font.setPointSize(10);
        tableWidget->setFont(font);
        tableWidget->setContextMenuPolicy(Qt::CustomContextMenu);
        tableWidget->setAlternatingRowColors(true);
        tableWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableWidget->horizontalHeader()->setStretchLastSection(true);
        tableWidget->verticalHeader()->setStretchLastSection(true);

        gridLayout->addWidget(tableWidget, 0, 0, 1, 1);


        retranslateUi(Channels);

        QMetaObject::connectSlotsByName(Channels);
    } // setupUi

    void retranslateUi(QDialog *Channels)
    {
        Channels->setWindowTitle(QApplication::translate("Channels", "Channels info", 0));
    } // retranslateUi

};

namespace Ui {
    class Channels: public Ui_Channels {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHANNELSCONTROL_H
