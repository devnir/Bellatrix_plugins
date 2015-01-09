/********************************************************************************
** Form generated from reading UI file 'SatView.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SATVIEW_H
#define UI_SATVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_SatView
{
public:
    QGridLayout *gridLayout;
    QGraphicsView *graphicsView;

    void setupUi(QDialog *SatView)
    {
        if (SatView->objectName().isEmpty())
            SatView->setObjectName(QStringLiteral("SatView"));
        SatView->resize(313, 313);
        SatView->setSizeIncrement(QSize(1, 1));
        SatView->setBaseSize(QSize(0, 0));
        SatView->setSizeGripEnabled(true);
        gridLayout = new QGridLayout(SatView);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SetMinimumSize);
        graphicsView = new QGraphicsView(SatView);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setMinimumSize(QSize(295, 295));
        graphicsView->setMaximumSize(QSize(9999, 9999));
        QFont font;
        font.setFamily(QStringLiteral("Courier New"));
        font.setPointSize(8);
        graphicsView->setFont(font);
        graphicsView->setLineWidth(0);
        graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        graphicsView->setRenderHints(QPainter::Antialiasing|QPainter::HighQualityAntialiasing|QPainter::NonCosmeticDefaultPen|QPainter::TextAntialiasing);
        graphicsView->setResizeAnchor(QGraphicsView::AnchorViewCenter);
        graphicsView->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);

        gridLayout->addWidget(graphicsView, 0, 0, 1, 1);


        retranslateUi(SatView);

        QMetaObject::connectSlotsByName(SatView);
    } // setupUi

    void retranslateUi(QDialog *SatView)
    {
        SatView->setWindowTitle(QApplication::translate("SatView", "Sat view", 0));
    } // retranslateUi

};

namespace Ui {
    class SatView: public Ui_SatView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SATVIEW_H
