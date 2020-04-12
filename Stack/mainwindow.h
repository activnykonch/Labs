#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <stack.h>
#include <QDebug>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void convert();
    void calculate();

private slots:
    void on_pushButton_clicked();
    void showData();
    void on_button_1_clicked();

    void on_button_2_clicked();

    void on_button_3_clicked();

    void on_button_4_clicked();

    void on_button_5_clicked();

    void on_button_6_clicked();

    void on_button_7_clicked();

    void on_button_8_clicked();

    void on_button_9_clicked();

    void on_button_0_clicked();

    void on_left_bracket_clicked();

    void on_button_minus_clicked();

    void on_button_clear_clicked();

    void on_right_bracket_clicked();

    void on_button_dev_clicked();

    void on_button_mult_clicked();

    void on_button_plus_clicked();

    void on_button_dot_clicked();

    void on_button_delete_clicked();

signals:
    void showResult();
private:
    Ui::MainWindow *ui;
    QString out;
    bool toConvert;
};
#endif // MAINWINDOW_H
