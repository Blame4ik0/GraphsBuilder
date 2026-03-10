/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include <graphwidget.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    GraphWidget *widget;
    QPushButton *colorOpener;
    QPushButton *vertexSelect;
    QPushButton *edgeSelect;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1280, 720);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        widget = new GraphWidget(centralwidget);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(0, 39, 1280, 681));
        colorOpener = new QPushButton(centralwidget);
        colorOpener->setObjectName("colorOpener");
        colorOpener->setGeometry(QRect(10, 10, 91, 24));
        vertexSelect = new QPushButton(centralwidget);
        vertexSelect->setObjectName("vertexSelect");
        vertexSelect->setGeometry(QRect(121, 10, 80, 24));
        QIcon icon(QIcon::fromTheme(QIcon::ThemeIcon::DriveOptical));
        vertexSelect->setIcon(icon);
        edgeSelect = new QPushButton(centralwidget);
        edgeSelect->setObjectName("edgeSelect");
        edgeSelect->setGeometry(QRect(210, 10, 80, 24));
        QIcon icon1(QIcon::fromTheme(QIcon::ThemeIcon::GoUp));
        edgeSelect->setIcon(icon1);
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Graphs Builder v1.3", nullptr));
        colorOpener->setText(QCoreApplication::translate("MainWindow", "Select colour", nullptr));
        vertexSelect->setText(QCoreApplication::translate("MainWindow", "Vertex", nullptr));
        edgeSelect->setText(QCoreApplication::translate("MainWindow", "Edge", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
