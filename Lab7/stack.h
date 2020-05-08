#ifndef STACK_H
#define STACK_H

template<typename T>
class Stack
{
public:
    Stack();
    ~Stack();

    void pop();
    void push(T data);
    void removeAt(int index);
    T peek();
    int getSize() {return size;}
    void copy(Stack* st);

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
Stack<T>::Stack()
{
    size=0;
    head=nullptr;
}
template<typename T>
Stack<T>::~Stack()
{
    while(size) this->pop();
}

template<typename T>
void Stack<T>::pop()
{
    removeAt(size-1);
}

template<typename T>
void Stack<T>::push(T data)
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
void Stack<T>::removeAt(int index)
{
    if(index==0){
        Node<T> *temp = head;
        head=head->pNext;
        delete  temp;
        size--;
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
T Stack<T>::peek()
{
    Node<T>* current = this->head;
    while(current->pNext!=nullptr){
        current=current->pNext;
    }
    return current->data;
}

template<typename T>
void Stack<T>::copy(Stack* st){
    Stack* temp = new Stack;
    while(size!=0){
        temp->push(this->peek());
        st->push(this->peek());
        this->pop();
    }
    while(temp->size!=0){
        this->push(temp->peek());
        temp->pop();
    }
    delete temp;
}
#endif // STACK_H
