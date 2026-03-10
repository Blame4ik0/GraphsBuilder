#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QColorDialog>

#define WINDOW_W 1280
#define WINDOW_H 720

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_colorOpener_clicked();
    void on_vertexSelect_clicked();
    void on_edgeSelect_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
