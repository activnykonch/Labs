#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "hashing.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void updateHashMap();

private slots:
    void on_add_element_clicked();

    void on_find_element_clicked();

    void on_delete_element_clicked();

    void on_solve_task_clicked();

    void on_fill_rand_clicked();

private:
    Ui::MainWindow *ui;
    Hashing<QString>* hashmap;

};
#endif // MAINWINDOW_H
