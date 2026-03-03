#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    resize(WINDOW_W, WINDOW_H);
    setFixedSize(WINDOW_W, WINDOW_H);
    ui->widget->resize(WINDOW_W, WINDOW_H);
    ui->widget->setFixedSize(WINDOW_W, WINDOW_H);
}

MainWindow::~MainWindow()
{
    delete ui;
}
