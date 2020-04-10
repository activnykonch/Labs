#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <database.h>
#include <search.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void writeInfoSignal();
    void addInfoSignal(int amount);

private slots:
    void show_data();

    void on_addInfo_clicked();

    void on_exit_clicked();

    void on_comboBox_activated(int index);

    void on_Edit_clicked();

    void on_Save_clicked();

    void on_Delete_clicked();

    void on_Search_clicked();

    void on_Sort_clicked();

private:
    Ui::MainWindow *ui;
    database* patient;
    int amount=0;
    int chosen=0;
};
#endif // MAINWINDOW_H
