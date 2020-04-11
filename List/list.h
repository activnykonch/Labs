#ifndef LIST_H
#define LIST_H

template<typename T>
class List
{
public:
    List();
    ~List();

    void pop_front();
    void push_front(T data);
    void pop_back();
    void push_back(T data);
    void insert(T data, int index);
    void removeAt(int index);
    void clear();
    int getSize() {return size;}
    T& operator[](const int index);

private:
    template<typename Tem>
    class Node{
    public:
        Node* pNext;
        Tem data;
        Node(Tem data = Tem(), Node* pNext=nullptr){
            this->data = data;
            this->pNext = pNext;
        }
    };
    Node<T>* head;
    int size;
};

template<typename T>
List<T>::List()
{
    size=0;
    head=nullptr;
}
template<typename T>
List<T>::~List()
{
    clear();
}

template<typename T>
void List<T>::pop_front()
{
    Node<T> *temp = head;
    head=head->pNext;
    delete  temp;
    size--;
}

template<typename T>
void List<T>::push_front(T data)
{
    head = new Node<T>(data, head);
    size++;
}

template<typename T>
void List<T>::pop_back()
{
    removeAt(size-1);
}

template<typename T>
void List<T>::push_back(T data)
{
    if(head==nullptr){
        head=new Node<T>(data);
    }
    else{
        Node<T>* current = this->head;
        while(current->pNext!=nullptr){
            current=current->pNext;
        }
        current->pNext = new Node<T> (data);
    }
    size++;
}

template<typename T>
void List<T>::insert(T data, int index)
{
    if(index==0){
        push_front(data);
    }else{
    Node<T> *previous = this->head;
    for(int i=0; i<index-1; ++i ){
        previous=previous->pNext;
    }
    previous->pNext = new Node<T>(data, previous->pNext);
    size++;
    }
}

template<typename T>
void List<T>::removeAt(int index)
{
    if(index==0){
        pop_front();
    }else{
        Node<T>* previous = this->head;
        for(int i=0; i<index-1; i++){
            previous=previous->pNext;
        }
        Node<T>* toDelete = previous->pNext;
        previous->pNext=toDelete->pNext;
        delete toDelete;
        size--;
    }
}

template<typename T>
void List<T>::clear()
{
    while(size){
        pop_front();
    }
}

template<typename T>
T &List<T>::operator[](const int index)
{
    int counter = 0;
    Node<T> *current =this->head;
    while(current!=nullptr){
        if(counter == index){
            return current->data;
        }
        current = current->pNext;
        counter++;
    }
}


#endif // LIST_H
