#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_fill_rand_clicked()
{
    pos.~List();
    neg.~List();
    ui->rand_nums->clear();
    srand(time(NULL));
    QString str="";
    int b=rand()%20;
    for(int i=0; i<b;i++){
        pos.PushBack(rand()%101-50);
        str+=QString::number(pos[i]) + " ";
    }
    ui->rand_nums->setText(str);
    ui->pos->clear();
    ui->neg->clear();
}

void MainWindow::on_split_clicked()
{
    QString Neg="";
    QString Pos="";
    for(int i=0; i<pos.GetSize(); i++){
        if(pos[i]<0){
            Node<int>* temp = pos.refReturn(i);
            pos.DeleteT(i);
            neg.PushFront(temp);
            i--;
    }
    }
    for(int i=0; i<neg.GetSize(); i++){
        Neg+=QString::number(neg[i]) + " ";
    }
    for(int i=0; i<pos.GetSize(); i++){
        Pos+=QString::number(pos[i]) + " ";
    }
    ui->pos->setText(Pos);
    ui->neg->setText(Neg);
}
