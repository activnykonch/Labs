#ifndef QUEUE_H
#define QUEUE_H


//Класс узла, хранит ссылки на след, пред ячейки памяти
template<class T>
class Node
{
public:
    Node();
    Node(const T& data);
    ~Node();
public:
    T data;
    Node* next;
    Node* prev;
};

//Реализация шаблонноой очереди
template<class T>
class Queue : Node<T>
{
public:
    Queue();

    ~Queue();

    void PushBack(const T& data);

    void PopFront();

    int GetSize();

    T& operator[](int list_pos);
    T& operator[](int list_pos) const;
public:

    Node<T>* head;

    Node<T>* tail;

    int size;
};

template<class T>
Node<T>::Node()
{
    this->next = this->prev = nullptr;
}

template<class T>
Node<T>::~Node()
{
    this->next = nullptr;
    this->prev = nullptr;
}

template<class T>
Node<T>::Node(const T& data)
{
    this->data = data;
    this->next = nullptr;
    this->prev = nullptr;
}

template<class T>
Queue<T>::Queue()
{
    this->size = 0;
    this->tail = nullptr;
    this->head = nullptr;
}

template<class T>
Queue<T>::~Queue()
{
    while (size)
    {
        this->PopFront();
    }
}

template<class T>
void Queue<T>::PushBack(const T& data)
{
    if (this->tail != nullptr)
    {
        Node<T>* newTail = new Node<T>(data);
        newTail->prev = this->tail;
        this->tail->next = newTail;
        this->tail = newTail;
        this->size++;
    }
    else
    {
        this->tail = new Node<T>(data);
        this->head = this->tail;
        this->size++;
    }
}

template<class T>
void Queue<T>::PopFront()
{
    if (this->size == 1)
    {
        delete this->head;
        this-> head = this->tail = nullptr;
        this->size--;
    }
    else
    {
        Node<T>* temp = head;
        head = head->next;
        delete temp;
        this->size--;
    }
}

template<class T>
int Queue<T>::GetSize()
{
    return this->size;
}

template<class T>
T& Queue<T>::operator[](int list_pos)
{
    if ((list_pos < (this->size) / 2) && (list_pos < this->size))
    {
        Node<T>* ptr = this->head;
        for (int i = 0; i < list_pos; ++i)
        {
            ptr = ptr->next;
        }
        return ptr->data;
    }
    else if (list_pos < this->size)
    {
        Node<T>* ptr = this->tail;
        for (int i = this->size - 1; i > list_pos; --i)
        {
            ptr = ptr->prev;
        }
        return ptr->data;
    }
}

template<class T>
T& Queue<T>::operator[](int list_pos) const
{
    if ((list_pos < (this->size) / 2) && (list_pos < this->size))
    {
        Node<T>* ptr = this->head;
        for (int i = 0; i < list_pos; ++i)
        {
            ptr = ptr->next;
        }
        return ptr->data;
    }
    else if (list_pos < this->size)
    {
        Node<T>* ptr = this->tail;
        for (int i = this->size - 1; i > list_pos; --i)
        {
            ptr = ptr->prev;
        }
        return ptr->data;
    }
}

#endif // QUEUE_H
