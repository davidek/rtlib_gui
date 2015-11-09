/********************************************************************************
** Form generated from reading UI file 'traceviewer.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TRACEVIEWER_H
#define UI_TRACEVIEWER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TraceViewer
{
public:
    QPushButton *showSchedButton;
    QPushButton *fileButton;

    void setupUi(QWidget *TraceViewer)
    {
        if (TraceViewer->objectName().isEmpty())
            TraceViewer->setObjectName(QStringLiteral("TraceViewer"));
        TraceViewer->resize(400, 300);
        showSchedButton = new QPushButton(TraceViewer);
        showSchedButton->setObjectName(QStringLiteral("showSchedButton"));
        showSchedButton->setGeometry(QRect(40, 60, 91, 23));
        fileButton = new QPushButton(TraceViewer);
        fileButton->setObjectName(QStringLiteral("fileButton"));
        fileButton->setGeometry(QRect(50, 20, 75, 23));

        retranslateUi(TraceViewer);

        QMetaObject::connectSlotsByName(TraceViewer);
    } // setupUi

    void retranslateUi(QWidget *TraceViewer)
    {
        TraceViewer->setWindowTitle(QApplication::translate("TraceViewer", "Form", 0));
        showSchedButton->setText(QApplication::translate("TraceViewer", "Show Schedule", 0));
        fileButton->setText(QApplication::translate("TraceViewer", "Select File", 0));
    } // retranslateUi

};

namespace Ui {
    class TraceViewer: public Ui_TraceViewer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TRACEVIEWER_H
