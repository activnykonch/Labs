#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(this, &MainWindow::showResult, this, &MainWindow::showData);
    out="";
    toConvert=true;
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool isDigit(QChar a){
    return ((a>='0' && a<='9') || a=='.');
}

bool isVariable(QChar q){
    return (q>='a' && q<='z');
}

int priority(QChar a){
    if(a=='(') return 1;
    else if(a=='+' || a=='-') return 2;
    else if(a=='*' || a=='/') return 3;
    else return 0;
}

void MainWindow::convert(){
    QString str;
    str=ui->lineEdit->text();
    if((!isDigit(str[0])) && str[0]!='(' && !isVariable(str[0].toLower())){
        QMessageBox::warning(this, "Error", "Syntax error");
        toConvert=false;
    }
    out="";
    int brackets = 0;
    Stack<QChar> st;
    if(toConvert)
        for(int i=0; i<str.length(); i++){
            if(str[i].isSpace()) continue;
            if(isDigit(str[i])) {
                out += str[i];
                continue;
            }
            else if(isVariable(str[i].toLower())){
                if(str[i].toLower() == 'a'){
                    if(ui->a_field->text().isEmpty()){
                        QMessageBox::warning(this, "Error", "No value for variable A");
                        toConvert = false;
                        break;
                    }
                    else out += ui->a_field->text();
                } else
                if(str[i].toLower() == 'b'){
                    if(ui->b_field->text().isEmpty()){
                        QMessageBox::warning(this, "Error", "No value for variable B");
                        toConvert = false;
                        break;
                    }
                    else out += ui->b_field->text();
                } else
                if(str[i].toLower() == 'c'){
                    if(ui->c_field->text().isEmpty()){
                        QMessageBox::warning(this, "Error", "No value for variable C");
                        toConvert = false;
                        break;
                    }
                    else out += ui->c_field->text();
                } else
                if(str[i].toLower() == 'd'){
                    if(ui->d_field->text().isEmpty()){
                        QMessageBox::warning(this, "Error", "No value for variable D");
                        toConvert = false;
                        break;
                    }
                    else out += ui->d_field->text();
                } else
                if(str[i].toLower() == 'e'){
                    if(ui->e_field->text().isEmpty()){
                        QMessageBox::warning(this, "Error", "No value for variable E");
                        toConvert = false;
                        break;
                    }
                    else out += ui->e_field->text();
                } else{
                    QMessageBox::warning(this, "Error", "Usage of not allowed variable " + str[i]);
                    toConvert = false;
                    break;
                }
                continue;
            }
            else{
                if(str[i]=='('){
                    st.push(str[i]);
                    if(i!=0) out+=" ";
                    brackets++;
                    continue;
                }
                if(str[i]==')'){
                    if(!brackets){
                        QMessageBox::warning(this, "Error", "Syntax error");
                        out=ui->lineEdit->text();
                        toConvert=false;
                        break;
                    }
                    while(st.peek()!='('){
                        out+=" ";
                        out+=st.peek();
                        st.pop();
                    }
                    st.pop();
                    brackets--;
                    continue;
                }
                if(str[i]=='+'||str[i]=='-'||str[i]=='*'||str[i]=='/'){
                    out+=" ";
                    if(st.getSize()==0){
                        st.push(str[i]);
                        continue;
                    }else{
                        if(priority(str[i])>priority(st.peek())){
                            st.push(str[i]);
                            continue;
                        }else{
                            while(priority(st.peek())>=priority(str[i])){
                                out+=" ";
                                out+=st.peek();
                                st.pop();
                                if(st.getSize()==0) break;
                            }
                            out+=" ";
                            st.push(str[i]);
                            continue;
                        }
                    }
                }
            }
        }
    while(st.getSize()!=0){
        out+=" ";
        out+=st.peek();
        st.pop();
    }
    if(brackets){
        QMessageBox::warning(this, "Error", "Wrong number of brackets");
        out=ui->lineEdit->text();
        toConvert=false;
    }
    qDebug() << out;
    while(st.getSize()!=0) st.pop();
}

bool isOper(QString a){
    return (a=="+" || a=="-" || a=="*" || a=="/");
}

void MainWindow::calculate(){
    Stack<float> fl;
    QStringList lst;
    lst = out.split(" ");
    for(int i=0; i<lst.size(); i++){
        if(lst[i]=="") continue;
        if(!isOper(lst[i])) fl.push(lst[i].toFloat());
        else{
            float a = fl.peek();
            fl.pop();
            float b = fl.peek();
            fl.pop();
            if(lst[i]=="+"){
                fl.push(b+a);
                continue;
            }
            if(lst[i]=="-"){
                fl.push(b-a);
                continue;
            }
            if(lst[i]=="*"){
                fl.push(b*a);
                continue;
            }
            if(lst[i]=="/"){
                if(a==0){
                    out="Error";
                    break;
                }
                fl.push(b/a);
                continue;
            }
        }
    }
    if(fl.getSize()!=0)out=QString::number(fl.peek());
    while(fl.getSize()!=0) fl.pop();
}

void MainWindow::on_pushButton_clicked()
{
    toConvert=true;
    convert();
    if(toConvert)calculate();
    emit showResult();
}

void MainWindow::showData(){
    ui->lineEdit->setText(out);
}
//8.5/(0.3*(2.4+7.9))-1.6

void MainWindow::on_button_1_clicked()
{
    QString str =ui->lineEdit->text();
    str+="1";
    ui->lineEdit->setText(str);
}


void MainWindow::on_button_2_clicked()
{
    QString str =ui->lineEdit->text();
    str+="2";
    ui->lineEdit->setText(str);
}

void MainWindow::on_button_3_clicked()
{
    QString str =ui->lineEdit->text();
    str+="3";
    ui->lineEdit->setText(str);
}

void MainWindow::on_button_4_clicked()
{
    QString str =ui->lineEdit->text();
    str+="4";
    ui->lineEdit->setText(str);
}

void MainWindow::on_button_5_clicked()
{
    QString str =ui->lineEdit->text();
    str+="5";
    ui->lineEdit->setText(str);
}

void MainWindow::on_button_6_clicked()
{
    QString str =ui->lineEdit->text();
    str+="6";
    ui->lineEdit->setText(str);
}

void MainWindow::on_button_7_clicked()
{
    QString str =ui->lineEdit->text();
    str+="7";
    ui->lineEdit->setText(str);
}

void MainWindow::on_button_8_clicked()
{
    QString str =ui->lineEdit->text();
    str+="8";
    ui->lineEdit->setText(str);
}

void MainWindow::on_button_9_clicked()
{
    QString str =ui->lineEdit->text();
    str+="9";
    ui->lineEdit->setText(str);
}

void MainWindow::on_button_0_clicked()
{
    QString str =ui->lineEdit->text();
    str+="0";
    ui->lineEdit->setText(str);
}

void MainWindow::on_left_bracket_clicked()
{
    QString str =ui->lineEdit->text();
    str+="(";
    ui->lineEdit->setText(str);
}

void MainWindow::on_button_minus_clicked()
{
    QString str =ui->lineEdit->text();
    str+="-";
    ui->lineEdit->setText(str);
}

void MainWindow::on_button_clear_clicked()
{
    ui->lineEdit->clear();
}

void MainWindow::on_right_bracket_clicked()
{
    QString str =ui->lineEdit->text();
    str+=")";
    ui->lineEdit->setText(str);
}

void MainWindow::on_button_dev_clicked()
{
    QString str =ui->lineEdit->text();
    str+="/";
    ui->lineEdit->setText(str);
}

void MainWindow::on_button_mult_clicked()
{
    QString str =ui->lineEdit->text();
    str+="*";
    ui->lineEdit->setText(str);
}

void MainWindow::on_button_plus_clicked()
{
    QString str =ui->lineEdit->text();
    str+="+";
    ui->lineEdit->setText(str);
}

void MainWindow::on_button_dot_clicked()
{
    QString str =ui->lineEdit->text();
    str+=".";
    ui->lineEdit->setText(str);
}

void MainWindow::on_button_delete_clicked()
{
    QString str =ui->lineEdit->text();
    str.chop(1);
    ui->lineEdit->setText(str);
}

void MainWindow::on_a_button_clicked()
{
    QString str =ui->lineEdit->text();
    str+="a";
    ui->lineEdit->setText(str);
}

void MainWindow::on_b_button_clicked()
{
    QString str =ui->lineEdit->text();
    str+="b";
    ui->lineEdit->setText(str);
}

void MainWindow::on_c_button_clicked()
{
    QString str =ui->lineEdit->text();
    str+="c";
    ui->lineEdit->setText(str);
}

void MainWindow::on_d_button_clicked()
{
    QString str =ui->lineEdit->text();
    str+="d";
    ui->lineEdit->setText(str);
}

void MainWindow::on_e_button_clicked()
{
    QString str =ui->lineEdit->text();
    str+="e";
    ui->lineEdit->setText(str);
}

void MainWindow::on_clear_vars_clicked()
{
    ui->a_field->clear();
    ui->b_field->clear();
    ui->c_field->clear();
    ui->d_field->clear();
    ui->e_field->clear();
}
