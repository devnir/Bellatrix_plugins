/********************************************************************************
** Form generated from reading UI file 'debugViterbi.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEBUGVITERBI_H
#define UI_DEBUGVITERBI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_debugViterbi
{
public:
    QPushButton *pushButton;
    QLabel *status;

    void setupUi(QDialog *debugViterbi)
    {
        if (debugViterbi->objectName().isEmpty())
            debugViterbi->setObjectName(QStringLiteral("debugViterbi"));
        debugViterbi->resize(743, 449);
        pushButton = new QPushButton(debugViterbi);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(9, 213, 75, 23));
        status = new QLabel(debugViterbi);
        status->setObjectName(QStringLiteral("status"));
        status->setGeometry(QRect(10, 170, 47, 13));

        retranslateUi(debugViterbi);

        QMetaObject::connectSlotsByName(debugViterbi);
    } // setupUi

    void retranslateUi(QDialog *debugViterbi)
    {
        debugViterbi->setWindowTitle(QApplication::translate("debugViterbi", "Dialog", 0));
        pushButton->setText(QApplication::translate("debugViterbi", "Init", 0));
        status->setText(QApplication::translate("debugViterbi", "TextLabel", 0));
    } // retranslateUi

};

namespace Ui {
    class debugViterbi: public Ui_debugViterbi {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEBUGVITERBI_H
