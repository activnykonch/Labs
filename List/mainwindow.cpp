#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDebug"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    p = new Product();
    connect(ui->comboBox, QOverload<int>::of(&QComboBox::activated), [=](){this->show_info();});


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_add_info_clicked()
{
    QString str=ui->name->text();
    ui->comboBox->addItem(str);
    p->setName(str);
    ui->name->clear();
    str=ui->amount->text();
    p->setAmount(str.toInt());
    ui->amount->clear();
    str=ui->guild->text();
    p->setGuild(str.toInt());
    ui->guild->clear();
    lst.push_back(*p);
}

void MainWindow::show_info()
{
    QString str="";
    ui->textBrowser->setAcceptRichText(true);
    ui->textBrowser->acceptRichText();
    str+=lst[chosen].getName() + " " + QString::number(lst[chosen].getAmount()) + " " + QString::number(lst[chosen].getGuild()) + "\n";
    ui->textBrowser->setText(str);
    ui->name->clear();
    ui->amount->clear();
    ui->guild->clear();
}

void MainWindow::on_comboBox_activated(int index)
{
    chosen=index;
}

void MainWindow::on_show_all_clicked()
{
    QString str="";
    ui->textBrowser->setAcceptRichText(true);
    ui->textBrowser->acceptRichText();
    for(int i=0; i<lst.getSize(); i++)
        str+=lst[i].getName() + " " + QString::number(lst[i].getAmount()) + " " + QString::number(lst[i].getGuild()) + "\n";
    if(str!="")ui->textBrowser->setText(str);
    else ui->textBrowser->setText("No data");
    ui->name->clear();
    ui->amount->clear();
    ui->guild->clear();
}

void MainWindow::on_delete_2_clicked()
{
    if(lst.getSize()>0){
    lst.removeAt(chosen);
    ui->comboBox->removeItem(chosen);
    ui->name->clear();
    ui->amount->clear();
    ui->guild->clear();
    }
}

void MainWindow::on_search_clicked()
{
    int guild = ui->guild->text().toInt();
    QString str="";
    str=ui->name->text();
    if(str==""){
    if(guild==0) ui->textBrowser->setText("No matches");
    else{
        int amount=ui->amount->text().toInt();
        if(amount==0){
            for(int i=0; i<lst.getSize(); i++){
                if(lst[i].getGuild()==guild) str+=lst[i].getName() + " " + QString::number(lst[i].getAmount()) + " " + QString::number(lst[i].getGuild()) + "\n";
            }
            if(str!="")ui->textBrowser->setText(str);
            else ui->textBrowser->setText("No matches");
        }else{
            for(int i=0; i<lst.getSize(); i++){
                if(lst[i].getGuild()==guild && lst[i].getAmount()>=amount) str+=lst[i].getName() + " " + QString::number(lst[i].getAmount()) + " " + QString::number(lst[i].getGuild()) + "\n";
            }
            if(str!="")ui->textBrowser->setText(str);
            else ui->textBrowser->setText("No matches");
        }
    }
    }else{
        QString check = str;
        str="";
        for(int i=0; i<lst.getSize(); i++){
            if(lst[i].getName()==check){
                str+=lst[i].getName() + " " + QString::number(lst[i].getAmount()) + " " + QString::number(lst[i].getGuild()) + "\n";
                break;
            }
        }
    }
    if(str!="")ui->textBrowser->setText(str);
    else ui->textBrowser->setText("No matches");
    ui->name->clear();
    ui->amount->clear();
    ui->guild->clear();
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    chosen=index;
}

void MainWindow::on_exit_clicked()
{
    exit(0);
}
