#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMap>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->treeView->setSelectionMode(QAbstractItemView::NoSelection);
    tree = new Tree<QString>();
    ui->find->setValidator(new QRegExpValidator(*new QRegExp("[1-9][0-9]+"), this));
    ui->del->setValidator(new QRegExpValidator(*new QRegExp("[1-9][0-9]+"), this));
    ui->to_tree->setCheckState(Qt::Checked);

    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setSelectionMode(QAbstractItemView::NoSelection);
    ui->tableWidget->setFocusPolicy(Qt::NoFocus);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_add_node_clicked()
{
    QString data = ui->data->text();
    QString key = ui->key->text();

    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
    int currentRow = ui->tableWidget->rowCount()-1;
    ui->tableWidget->setItem(currentRow, 0, new QTableWidgetItem(data));
    ui->tableWidget->setItem(currentRow, 1, new QTableWidgetItem(key));

    if(ui->to_tree->isChecked()){
        tree->addNode(data, key.toInt());
        updateTreeView();
    }

    ui->data->clear();
    ui->key->clear();
}


void MainWindow::fillTreeView(QTreeWidgetItem *parentItem, Node<QString> *node)
{
    if (node != nullptr) {
        QTreeWidgetItem *item = new QTreeWidgetItem();
        QString itemText = "Key(" + QString::number(node->key) + "), " + "Data("
                + node->data + ")";
        item->setText(0, itemText);
        if (parentItem == nullptr) {
            ui->treeView->addTopLevelItem(item);
        } else {
            parentItem->addChild(item);
        }
        item->setExpanded(true);
        fillTreeView(item, node->left);
        fillTreeView(item, node->right);
    }
}

void MainWindow::updateTreeView()
{
    ui->treeView->clear();

    if (tree->Root != nullptr) {
        fillTreeView(nullptr, tree->Root);
    }
}

void MainWindow::on_balance_tree_clicked()
{
    tree->balanceTree();
    updateTreeView();
}

void MainWindow::on_find_node_clicked()
{
    QString str="";
    ui->textBrowser->clear();
    str=ui->find->text();
    int key=0;
    if(str!=""){
        key=str.toInt();
        Node<QString> *found = tree->findNode(key);
        if(found!=nullptr){
            str="";
            str+="Data: " + found->data + " Key: " + QString::number(found->key);
            ui->textBrowser->appendPlainText(str);
        }
        else ui->textBrowser->appendPlainText("No data found by your key");
    }
    ui->find->clear();
}

void MainWindow::on_delete_node_clicked()
{
    if(ui->del->text().isEmpty()){
        QString str = "Enter key";
        ui->textBrowser->appendPlainText(str);
    }else {
        int key=ui->del->text().toInt();
        tree->deleteNode(key);
        ui->del->clear();
        updateTreeView();
    }
}

void MainWindow::on_del_tree_clicked()
{
    tree->deleteTree(tree->Root);
    updateTreeView();
}

void MainWindow::preOrder(Node<QString> *localRoot)
{
    if (localRoot != nullptr) {
        QString output = "Key : " + QString::number(localRoot->key)
                + ", Data : " + localRoot->data + ".";

        ui->textBrowser->appendPlainText(output);
        preOrder(localRoot->left);
        preOrder(localRoot->right);
    }
}

void MainWindow::inOrder(Node<QString> *localRoot)
{
    if (localRoot != nullptr) {
        QString output = "Key : " + QString::number(localRoot->key)
                + ", Data : " + localRoot->data + ".";

        inOrder(localRoot->left);
        ui->textBrowser->appendPlainText(output);
        inOrder(localRoot->right);
    }
}

void MainWindow::postOrder(Node<QString> *localRoot){
    if (localRoot != nullptr) {
        QString output = "Key : " + QString::number(localRoot->key)
                + ", Data : " + localRoot->data + ".";

        postOrder(localRoot->left);
        postOrder(localRoot->right);
        ui->textBrowser->appendPlainText(output);
    }
}

void MainWindow::on_pint_tree_clicked()
{
    ui->textBrowser->clear();

    if (ui->pre_order->isChecked()) {
        preOrder(tree->Root);
    } else if (ui->in_order->isChecked()) {
        inOrder(tree->Root);
    } else if (ui->post_order->isChecked()) {
        postOrder(tree->Root);
    }
}

void MainWindow::on_fill_from_table_clicked()
{
    if (tree->Root != nullptr) {
        tree->deleteTree(tree->Root);
    }

    int rowCount = ui->tableWidget->rowCount();
    for (int i = 0; i < rowCount; i++) {
        QString data = ui->tableWidget->item(i, 0)->text();
        int key = ui->tableWidget->item(i, 1)->text().toInt();

        tree->addNode(data, key);
    }

    updateTreeView();
}

void MainWindow::count(Node<QString>* nd, QMap<int, int> &m, int level){
    if(nd==nullptr) return;
    if(nd->left) count(nd->left, m, level+1);
    if(nd->left==nullptr && nd->right==nullptr) m[level]++;
    if(nd->right) count(nd->right, m, level+1);
}

void MainWindow::on_solve_task_clicked()
{
    ui->textBrowser->clear();
    Node<QString> *nd = tree->Root;
    QMap<int, int> m;
    count(nd, m, 0);
    for(auto i = m.begin(); i!=m.end(); i++) ui->textBrowser->appendPlainText("On level " + QString::number(i.key()) + " " + QString::number(i.value()) + " leave(s)");
}
