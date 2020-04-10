#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    patient=new database();
    connect(ui->comboBox, QOverload<int>::of(&QComboBox::activated), [=](){this->show_data();});
    QFile file("database.txt");
    file.open(QIODevice::ReadOnly);
    if(file.exists()){
        while(!file.atEnd()){
            patient=database::addPatient(patient, amount);
            QString str;
            str=file.readLine();
            QStringList list = str.split(" ");
            patient[amount].setLastName(list[0]);
            patient[amount].setFirstName(list[1]);
            patient[amount].setGender(list[2]);
            patient[amount].setAge(list[3].toInt());
            patient[amount].setChamber(list[4].toInt());
            patient[amount].setDiagnosis(list[4]);
            ui->comboBox->addItem(patient[amount].getLastName());
            amount++;
        }
    } else qDebug() << "file not found";
    file.close();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_addInfo_clicked()
{
    patient=database::addPatient(patient, amount);
    QString str = ui->last_name->text();
    patient[amount].setLastName(str);
    ui->last_name->clear();
    str = ui->first_name->text();
    patient[amount].setFirstName(str);
    ui->first_name->clear();
    str = ui->gender->text();
    patient[amount].setGender(str);
    ui->gender->clear();
    str = ui->age->text();
    patient[amount].setAge(str.toInt());
    ui->age->clear();
    str = ui->chamber->text();
    patient[amount].setChamber(str.toInt());
    ui->chamber->clear();
    str = ui->diagnosis->text();
    patient[amount].setDiagnosis(str);
    ui->diagnosis->clear();
    ui->comboBox->addItem(patient[amount].getLastName());
    patient[amount].addInfo();
    amount++;
}

void MainWindow::on_exit_clicked()
{
    exit(0);
}


void MainWindow::on_comboBox_activated(int index)
{
    chosen=index;
}

void MainWindow::show_data(){
    patient[chosen].readInfo(chosen);
    ui->textBrowser->setOverwriteMode(true);
    ui->textBrowser->setText(patient[chosen].getLastName()+"\n"+patient[chosen].getFirstName()+"\n"+patient[chosen].getGender()+"\n"+QString::number(patient[chosen].getAge())+"\n"
                             +QString::number(patient[chosen].getChamber())+"\n"+patient[chosen].getDiagnosis());
}

void MainWindow::on_Edit_clicked()
{
    ui->last_name->setText(patient[chosen].getLastName());
    ui->first_name->setText(patient[chosen].getFirstName());
    ui->gender->setText(patient[chosen].getGender());
    ui->age->setText(QString::number(patient[chosen].getAge()));
    ui->chamber->setText(QString::number(patient[chosen].getChamber()));
    ui->diagnosis->setText(patient[chosen].getDiagnosis());
}

void MainWindow::on_Save_clicked()
{
    ui->textBrowser->clear();
    QString str = ui->last_name->text();
    patient[chosen].setLastName(str);
    ui->last_name->clear();
    str = ui->first_name->text();
    patient[chosen].setFirstName(str);
    ui->first_name->clear();
    str = ui->gender->text();
    patient[chosen].setGender(str);
    ui->gender->clear();
    str = ui->age->text();
    patient[chosen].setAge(str.toInt());
    ui->age->clear();
    str = ui->chamber->text();
    patient[chosen].setChamber(str.toInt());
    ui->chamber->clear();
    str = ui->diagnosis->text();
    patient[chosen].setDiagnosis(str);
    ui->diagnosis->clear();
    QFile file("database.txt");
    file.open(QIODevice::WriteOnly);
    QTextStream write(&file);
    if(file.exists()){
        for(int i=0; i<amount; i++)
            write << patient[i].getLastName() << " " <<  patient[i].getFirstName() << " " << patient[i].getGender() << " " <<
                     patient[i].getAge() << " " << patient[i].getChamber() << " " << patient[i].getDiagnosis() << " " << "\n";
    }
    file.close();
    ui->comboBox->setItemText(chosen, patient[chosen].getLastName());
}

void MainWindow::on_Delete_clicked()
{
    ui->comboBox->removeItem(chosen);
    for(int i=chosen; i<amount-1; i++){
        patient[i]=patient[i+1];
    }
    patient[amount-1].~database();
    amount--;
    QFile file("database.txt");
    file.open(QIODevice::WriteOnly);
    QTextStream write(&file);
    if(file.exists()){
        for(int i=0; i<amount; i++)
            write << patient[i].getLastName() << " " <<  patient[i].getFirstName() << " " << patient[i].getGender() << " " <<
                     patient[i].getAge() << " " << patient[i].getChamber() << " " << patient[i].getDiagnosis() << " " << "\n";
    }
    file.close();
}

void MainWindow::on_Search_clicked()
{
    QString str;
    str = ui->last_name->text();
    if(str==""){
        str=ui->diagnosis->text();
        if(str==""){
            int num;
            num = (ui->chamber->text()).toInt();
            for(int i=0; i<amount; i++){
                if(num==patient[i].getChamber()) str+=patient[i].getLastName()+"\n";
            }
            if(str=="") ui->textBrowser->setText("No patients in chamber " +QString::number(num));
            else ui->textBrowser->setText("List of patients in chamber "+QString::number(num)+":\n"+str);
        }else{
            QString diag = str;
            str="";
            for(int i=0; i<amount; i++){
                if(diag==patient[i].getDiagnosis()) str+=patient[i].getLastName()+"\n";
            }
            if(str=="") ui->textBrowser->setText("No patients with diagnosis " +diag);
            else ui->textBrowser->setText("List of patients with diagnosis "+diag+":\n"+str);
        }
    }else{
        bool found = false;
        int searched;
        for(int i=0; i<amount; i++){
            if(str==patient[i].getLastName()){ searched=i; found = true; break;}
        }
        if(found) ui->textBrowser->setText(patient[searched].getLastName()+"\n"+patient[searched].getFirstName()+"\n"+patient[searched].getGender()+"\n"+QString::number(patient[searched].getAge())+"\n"
                                           +QString::number(patient[searched].getChamber())+"\n"+patient[searched].getDiagnosis());
        else ui->textBrowser->setText("Data of patient " + str + " is not found");
    }
}

void MainWindow::on_Sort_clicked()
{
    bool impos=false;
    QString str="";
    for(int i=0; i<amount; i++){
        for(int j=0; j<amount; j++){
            if(i==j) continue;
            if(patient[i].getGender()==patient[j].getGender()){
                if(patient[i].getDiagnosis()==patient[j].getDiagnosis()){
                    patient[j].setChamber(patient[i].getChamber());
                    impos = false;
                }
                else impos=true;
            }
        }
        if(impos) str+=patient[i].getLastName()+" " + patient[i].getFirstName() + " " +patient[i].getGender() + " "+ QString::number(patient[i].getAge()) + " " + patient[i].getDiagnosis() + "\n";
    }
    QFile file("database.txt");
    file.open(QIODevice::WriteOnly);
    QTextStream write(&file);
    if(file.exists()){
        for(int i=0; i<amount; i++)
            write << patient[i].getLastName() << " " <<  patient[i].getFirstName() << " " << patient[i].getGender() << " " <<
                     patient[i].getAge() << " " << patient[i].getChamber() << " " << patient[i].getDiagnosis() << " " << "\n";
    }
    file.close();
    if(str=="") ui->textBrowser->setText("All patients are provided with chambers");
    else ui->textBrowser->setText("List of patients who cannot be provided with chambers:\n"+str);
}
