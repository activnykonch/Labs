#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "list.h"
#include <time.h>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_fill_rand_clicked();

    void on_split_clicked();

private:
    Ui::MainWindow *ui;
    List<int> pos;
    List<int> neg;

};
#endif // MAINWINDOW_H
