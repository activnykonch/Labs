#ifndef NODE_H
#define NODE_H

template <class T>
    class Node {
    public:
        Node* left;
        Node* right;
        int key;
        unsigned char height;
        T data;
        Node(T data = T(), int key = 0, Node* left = nullptr, Node* right = nullptr) {
            this->data = data;
            this->right = right;
            this->left = left;
            this->key = key;
        }
};
#endif // NODE_H
