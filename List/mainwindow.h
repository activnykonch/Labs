#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "list.h"
#include "product.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void show_info();

private slots:
    void on_add_info_clicked();

    void on_comboBox_activated(int index);

    void on_show_all_clicked();

    void on_delete_2_clicked();

    void on_search_clicked();

    void on_comboBox_currentIndexChanged(int index);

    void on_exit_clicked();

private:
    Ui::MainWindow *ui;
    Product* p;
    List<Product> lst;
    int chosen;
};
#endif // MAINWINDOW_H
