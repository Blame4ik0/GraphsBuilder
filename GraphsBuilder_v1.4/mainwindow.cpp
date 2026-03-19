#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow (QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->widget->currentMode = 0;
}

MainWindow::~MainWindow ()
{
    delete ui;
}

void MainWindow::on_save_clicked ()
{
    QString path = QFileDialog::getSaveFileName(this, "Save graph", "", "Graph files (*.graph)");
    if (!path.isEmpty()) ui->widget->saveToFile(path);
}

void MainWindow::on_load_clicked ()
{
    QString path = QFileDialog::getOpenFileName(this, "Load graph", "", "Graph files (*.graph)");
    if (!path.isEmpty()) ui->widget->loadFromFile(path);
}

void MainWindow::on_colorOpener_clicked ()
{
    QColor color = QColorDialog::getColor(ui->widget->paintColor, this, "Select node colour");
    if (color.isValid()) ui->widget->setPaintColor(color);
}

void MainWindow::on_vertexSelect_clicked ()
{
    ui->vertexSelect->setChecked(true);
    ui->edgeSelect->setChecked(false);
    ui->moveModeSelect->setChecked(false);
    ui->widget->currentMode = 0;
    ui->widget->setFocus();
}

void MainWindow::on_edgeSelect_clicked ()
{
    ui->edgeSelect->setChecked(true);
    ui->vertexSelect->setChecked(false);
    ui->moveModeSelect->setChecked(false);
    ui->widget->currentMode = 1;
    ui->widget->setFocus();
}

void MainWindow::on_moveModeSelect_clicked ()
{
    ui->moveModeSelect->setChecked(true);
    ui->vertexSelect->setChecked(false);
    ui->edgeSelect->setChecked(false);
    ui->widget->currentMode = 2;
    ui->widget->setFocus();
}
