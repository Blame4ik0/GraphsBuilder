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
#include <QtWidgets/QHBoxLayout>
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
    QWidget *widget1;
    QHBoxLayout *horizontalLayout;
    QPushButton *save;
    QPushButton *load;
    QPushButton *colorOpener;
    QPushButton *vertexSelect;
    QPushButton *edgeSelect;
    QPushButton *moveModeSelect;

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
        widget1 = new QWidget(centralwidget);
        widget1->setObjectName("widget1");
        widget1->setGeometry(QRect(230, 10, 741, 26));
        horizontalLayout = new QHBoxLayout(widget1);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        save = new QPushButton(widget1);
        save->setObjectName("save");
        QIcon icon(QIcon::fromTheme(QIcon::ThemeIcon::DocumentSaveAs));
        save->setIcon(icon);

        horizontalLayout->addWidget(save);

        load = new QPushButton(widget1);
        load->setObjectName("load");
        QIcon icon1(QIcon::fromTheme(QIcon::ThemeIcon::DocumentOpen));
        load->setIcon(icon1);

        horizontalLayout->addWidget(load);

        colorOpener = new QPushButton(widget1);
        colorOpener->setObjectName("colorOpener");

        horizontalLayout->addWidget(colorOpener);

        vertexSelect = new QPushButton(widget1);
        vertexSelect->setObjectName("vertexSelect");
        QIcon icon2(QIcon::fromTheme(QIcon::ThemeIcon::DriveOptical));
        vertexSelect->setIcon(icon2);

        horizontalLayout->addWidget(vertexSelect);

        edgeSelect = new QPushButton(widget1);
        edgeSelect->setObjectName("edgeSelect");
        QIcon icon3(QIcon::fromTheme(QIcon::ThemeIcon::GoUp));
        edgeSelect->setIcon(icon3);

        horizontalLayout->addWidget(edgeSelect);

        moveModeSelect = new QPushButton(widget1);
        moveModeSelect->setObjectName("moveModeSelect");
        QIcon icon4(QIcon::fromTheme(QIcon::ThemeIcon::InputMouse));
        moveModeSelect->setIcon(icon4);

        horizontalLayout->addWidget(moveModeSelect);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Graphs Builder v1.3", nullptr));
        save->setText(QCoreApplication::translate("MainWindow", "Save File", nullptr));
        load->setText(QCoreApplication::translate("MainWindow", "Load File", nullptr));
        colorOpener->setText(QCoreApplication::translate("MainWindow", "Select colour", nullptr));
        vertexSelect->setText(QCoreApplication::translate("MainWindow", "Vertex", nullptr));
        edgeSelect->setText(QCoreApplication::translate("MainWindow", "Edge", nullptr));
        moveModeSelect->setText(QCoreApplication::translate("MainWindow", "Move", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
