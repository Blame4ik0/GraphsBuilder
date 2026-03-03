#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    resize(WINDOW_W, WINDOW_H);
    setFixedSize(WINDOW_W, WINDOW_H);
}

MainWindow::~MainWindow()
{
    delete ui;
}
