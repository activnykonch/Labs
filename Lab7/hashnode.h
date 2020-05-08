#ifndef HASHNODE_H
#define HASHNODE_H
template<class T>
class HashNode{
public:
    T data;
    int key;
    HashNode(T data, int key){
        this->data = data;
        this->key = key;
    }
};
#endif // HASHNODE_H
