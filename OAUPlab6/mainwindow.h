#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <tree.h>
#include <QTreeWidgetItem>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void fillTreeView(QTreeWidgetItem *parentItem, Node<QString> *node);
    void updateTreeView();
    void preOrder(Node<QString> *localRoot);
    void inOrder(Node<QString> *localRoot);
    void postOrder(Node<QString> *localRoot);
    void count(Node<QString>* nd, QMap<int, int> &m, int level);

private slots:
    void on_add_node_clicked();

    void on_balance_tree_clicked();

    void on_find_node_clicked();

    void on_delete_node_clicked();

    void on_del_tree_clicked();

    void on_pint_tree_clicked();

    void on_fill_from_table_clicked();

    void on_solve_task_clicked();

private:
    Ui::MainWindow *ui;
    Tree<QString> *tree;
    QTreeWidgetItem* items;
};
#endif // MAINWINDOW_H
