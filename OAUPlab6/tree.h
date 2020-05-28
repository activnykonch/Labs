#ifndef TREE_H
#define TREE_H
#include <node.h>
#include <QVector>
template <class T>
class Tree
{
public:
    Node<T>* Root;
    unsigned int size;
    Tree();
    ~Tree();

    void addNode(T data, int key);
    void showTree(Node<T>* n);
    void show();
    int getSize() { return size; }
    void keepNodes(Node<T> *localRoot, QVector<Node<T> *> &nodes);
    Node<T> *balanceNodes(QVector<Node<T> *> &nodes, int start, int end);
    void balanceTree();
    Node<T>* findNode(int key);
    void deleteNode(int key);
    Node<T>* replaceNode(Node<T>* toDel);

    void _deleteTree(Node<T> *localRoot);
    void deleteTree(Node<T> *localRoot);

};

template <class T>
Tree<T>::Tree() {
    Root = nullptr;
    size = 0;
}

template <class T>
Tree<T>::~Tree() {
}

template <class T>
void Tree<T>::addNode(T data, int key) {
    if (Root == nullptr) {
        Root = new Node<T>(data, key);
    }
    else {
        Node<T>* current = this->Root;
        while (true) {
            if (key < current->key) {
                if (current->left == nullptr) {
                    current->left = new Node<T>(data, key);
                    break;
                }
                else {
                    current = current->left;
                }
            }
            if (key > current->key) {
                if (current->right == nullptr) {
                    current->right = new Node<T>(data, key);
                    break;
                }
                else {
                    current = current->right;
                }
            }
            if (key == current->key) {
                size--;
                break;
            }
        }
    }
    size++;
}

template<class T>
void Tree<T>::keepNodes(Node<T> *localRoot, QVector<Node<T> *> &nodes)
{
    if (localRoot != nullptr) {
        keepNodes(localRoot->left, nodes);
        nodes.push_back(localRoot);
        keepNodes(localRoot->right, nodes);
    }
}

template<class T>
Node<T> *Tree<T>::balanceNodes(QVector<Node<T> *> &nodes, int start, int end)
{
    if (start > end) {
        return nullptr;
    }

    int mid = (start + end) / 2;
    Node<T> *localRoot = nodes[mid];

    localRoot->left = balanceNodes(nodes, start, mid - 1);
    localRoot->right = balanceNodes(nodes, mid + 1, end);
    return localRoot;
}

template<class T>
void Tree<T>::balanceTree()
{
    QVector<Node<T> *> nodes;
    keepNodes(Root, nodes);
    Root = balanceNodes(nodes, 0, nodes.size() - 1);
}

template<class T>
Node<T>* Tree<T>::findNode(int key){
    Node<T>* current = Root;

    if(current!=nullptr){
        while(current->key!=key){
            if(key<current->key)
                current=current->left;

            if(key>current->key)
                current=current->right;

            if(current==nullptr)
                return nullptr;
        }
    }
    return current;
}

template<class T>
void Tree<T>::deleteNode(int key){
    Node<T> *toDelete = Root;
    Node<T> *parent = Root;
    bool isLeft = false;

    if (toDelete != nullptr) {
        while (toDelete->key != key) {
            parent = toDelete;
            if (key < toDelete->key) {
                toDelete = toDelete->left;
            } else {
                toDelete = toDelete->right;
            }
            if (toDelete == nullptr) {
                return;
            }
        }

        if(toDelete != nullptr){
            if(toDelete->right == nullptr && toDelete->left == nullptr){
                if(isLeft) parent->left = nullptr;
                else parent->right = nullptr;
            }
            else if(toDelete->right == nullptr){
                if(isLeft) parent->left=toDelete->left;
                else parent->right=toDelete->left;
            }
            else if(toDelete->left == nullptr){
                if(isLeft) parent->left=toDelete->right;
                else parent->right=toDelete->right;
            }
            else{
                Node<T>* replace = replaceNode(toDelete);
                if(toDelete==Root)
                    Root=replace;
                else if(toDelete==parent->left)
                    parent->left=replace;
                else parent->right=replace;

                replace->left=toDelete->left;
            }
            delete toDelete;
        }
    }
}

template<class T>
Node<T>* Tree<T>::replaceNode(Node<T>* toDel){
    Node<T>* replace = toDel;
    Node<T>* replaceParent = toDel;
    Node<T>* current = toDel->right;
    while(current!=nullptr){
        replaceParent=replace;
        replace=current;
        current=current->left;
    }
    if(replace!=toDel->right){
        replaceParent->left=replace->right;
        replace->right=toDel->right;
    }
    return replace;
}

template<class T>
void Tree<T>::_deleteTree(Node<T> *localRoot)
{
    if (localRoot == nullptr) {
        return;
    }
    _deleteTree(localRoot->left);
    _deleteTree(localRoot->right);
    delete localRoot;
}

template<class T>
void Tree<T>::deleteTree(Node<T> *localRoot)
{
    _deleteTree(localRoot);
    if (localRoot==Root) {
        Root = nullptr;
    }
}
#endif // TREE_H
