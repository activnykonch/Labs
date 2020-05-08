#ifndef HASHING_H
#define HASHING_H
#include <QString>
#include "stack.h"
#include "hashnode.h"

template<class T>
class Hashing{
    int size;
    Stack<HashNode<T>*>* map;
public:
    Hashing();
    Hashing(int size = 0);
    ~Hashing();

    int GetSize(){ return size; }
    Stack<HashNode<T>*> *GetMap(){ return map; }

    int CalcHash(int key){ return key % size; }
    void AddNode(T data, int key);
    HashNode<T>* FindNode(int key);
    void DeleteNode(int key);

};

template<class T>
Hashing<T>::Hashing(int size){
    this->size = size;
    map = new Stack<HashNode<T>*>[size];
}

template<class T>
Hashing<T>::~Hashing(){
    delete  map;
}

template<class T>
void Hashing<T>::AddNode(T data, int key){
    HashNode<T>* nd = new HashNode<T>(data, key);
    key = CalcHash(key);
    map[key].push(nd);
}

template<class T>
HashNode<T>* Hashing<T>::FindNode(int key){
    for(int i=0; i<size; i++){
        Stack<HashNode<T>*>* temp = new Stack<HashNode<T>*>();
        HashNode<T>* fd;
        map[i].copy(temp);
        while(temp->getSize()){
            fd = temp->peek();
            if(fd->key == key){
                delete temp;
                return fd;
            }else{
                temp->pop();
            }
        }
        delete temp;
    }
    return nullptr;
}

template<class T>
void Hashing<T>::DeleteNode(int key){
    bool del = false;
    for(int i=0; i<size && !del; i++){
        Stack<HashNode<T>*>* temp = new Stack<HashNode<T>*>();
        HashNode<T>* fd;
        map[i].copy(temp);
        while(map[i].getSize()){
            map[i].pop();
        }
        while(temp->getSize()){
            fd = temp->peek();
            if(fd->key == key){
                del = true;
            }else map[i].push(fd);
            temp->pop();
        }
        delete temp;
    }
}
#endif // HASHING_H
