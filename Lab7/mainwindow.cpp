#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QRegExpValidator>
#include "stack.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    hashmap = new Hashing<QString>(32);
    qsrand(time(0));
    ui->key->setValidator(new QRegExpValidator(*new QRegExp("[1-9][0-9]+"), this));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_add_element_clicked()
{
    if(!ui->key->text().isEmpty()){
        int key = ui->key->text().toInt();
        QString data = ui->data->text();
        hashmap->AddNode(data, key);
        updateHashMap();
        ui->key->clear();
        ui->data->clear();
    }else QMessageBox::warning(this, "Key", "Fill in \"Key\" field");
}

void MainWindow::on_find_element_clicked()
{
    ui->output->clear();
    if(!ui->key->text().isEmpty()){
        int key = ui->key->text().toInt();
        HashNode<QString>* nd = hashmap->FindNode(key);
        if(nd==nullptr) QMessageBox::warning(this, "Key", "No element with key: " + QString::number(ui->key->text().toInt()));
        else{
            QString str = "Key: " + QString::number(nd->key)+ " Data: " + nd->data;
            ui->output->setText(str);
        }
        ui->key->clear();
    }else QMessageBox::warning(this, "Key", "Fill in \"Key\" field");
}

void MainWindow::on_delete_element_clicked()
{
    if(!ui->key->text().isEmpty()){
        int key = ui->key->text().toInt();
        hashmap->DeleteNode(key);
        updateHashMap();
        ui->key->clear();
    }else QMessageBox::warning(this, "Key", "Fill in \"Key\" field");
}

void MainWindow::updateHashMap()
{
    ui->hashmap_widget->clear();
    Stack<HashNode<QString>*>* temp = new Stack<HashNode<QString>*>();
    for (int i = 0; i < hashmap->GetSize(); i++) {
        QString hashMapLine = QString::number(i) + "  : ";
        hashmap->GetMap()[i].copy(temp);
        while(temp->getSize()){
            hashMapLine.append("Key: " + QString::number(temp->peek()->key) + " Data: " + temp->peek()->data + "   ");
            temp->pop();
        }
        ui->hashmap_widget->insertPlainText(hashMapLine + "\n");
    }
    delete temp;
}

void MainWindow::on_solve_task_clicked()
{
    ui->output->clear();
    Stack<HashNode<QString>*>* temp = new Stack<HashNode<QString>*>();
    int stnumber = 0;
    int value = 0;
    for(int i=0; i < hashmap->GetSize(); i++){
        hashmap->GetMap()[i].copy(temp);
        while(temp->getSize()){
            if(temp->peek()->key > value){
                value = temp->peek()->key;
                stnumber = i;
            }
            temp->pop();
        }
    }
    ui->output->setText("The largest key has stack number " + QString::number(stnumber) + " with the value " + QString::number(value));
    delete temp;
}

void MainWindow::on_fill_rand_clicked()
{
    int amount = qrand()%20 + 20;
    for(int i=0; i < amount; i++){
        int key = qrand() % 100;
        hashmap->AddNode("", key);
        updateHashMap();
    }
}
