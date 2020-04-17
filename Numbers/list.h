#ifndef LIST_H
#define LIST_H

#include "queue.h"

template<class T>
class List : public Queue<T>
{
public:

    List();
    ~List();
    void PushFront(const T& data);

    void PushFront(Node<T>* newHead);

    void Insert(const T& data, int pos);

    void Delete(int pos);

    List<T>& operator=(const List<T>& another);

    void PopBack();

    Node<T>* refReturn(int pos);
    void DeleteT(int list_pos);
};

template<class T>
List<T>::List()
{
    this->size = 0;
    this->tail = nullptr;
    this->head = nullptr;
}

template<class T>
List<T>::~List()
{
    while (this->size)
    {
        this->PopFront();
    }
}

template<class T>
void List<T>::PushFront(const T& data)
{
    if (this->head != nullptr)
    {
        Node<T>* newHead = new Node<T>(data);
        newHead->next = this->head;
        this->head->prev = newHead;
        this->head = newHead;
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
void List<T>::PushFront(Node<T>* newHead)
{
    if (this->head != nullptr)
    {
        newHead->next = this->head;
        this->head->prev = newHead;
        newHead->prev = nullptr;
        this->head = newHead;
        this->size++;
    }
    else
    {
        this->tail = newHead;
        newHead->prev = nullptr;
        newHead->next = nullptr;
        this->head = this->tail;
        this->size++;
    }
}

template<class T>
void List<T>::Insert(const T& data, int list_pos)
{
    Node<T>* temp = new Node<T>(data);
    if ((list_pos < (this->size) / 2))
    {
        if (!list_pos)
        {
            PushFront(data);
        }
        else
        {
            Node<T>* _ptr = this->head;
            for (int i = 0; i < list_pos; ++i)
            {
                _ptr = _ptr->next;
            }
            temp->next = _ptr;
            temp->prev = _ptr->prev;
            _ptr->prev->next = temp;
            _ptr->prev = temp;
            this->size++;
        }
    }
    else if (list_pos < this->size)
    {
        if (list_pos == this->size - 1)
        {
            PushBack(data);
        }
        else
        {
            Node<T>* _ptr = this->tail;
            for (int i = this->size - 1; i > list_pos; --i)
            {
                _ptr = _ptr->prev;
            }
            temp->next = _ptr;
            temp->prev = _ptr->prev;
            _ptr->prev->next = temp;
            _ptr->prev = temp;
            this->size++;
        }

    }
}

template<class T>
void List<T>::Delete(int list_pos)
{
    if (!list_pos)
    {
        this->PopFront();
    }
    else if (list_pos == this->size - 1)
    {
        this->PopBack();
    }
    else if ((list_pos < (this->size) / 2))
    {
        Node<T>* _ptr = this->head;
        for (int i = 0; i < list_pos; ++i)
        {
            _ptr = _ptr->next;
        }
        _ptr->prev->next = _ptr->next;
        _ptr->next->prev = _ptr->prev;
        delete _ptr;
        this->size--;
    }
    else if (list_pos < this->size)
    {
        Node<T>* _ptr = this->tail;
        for (int i = this->size - 1; i > list_pos; --i)
        {
            _ptr = _ptr->prev;
        }
        _ptr->prev->next = _ptr->next;
        _ptr->next->prev = _ptr->prev;
        delete _ptr;
        this->size--;
    }
}

template<class T>
void List<T>::DeleteT(int list_pos)
{
    if (!list_pos)
    {
        if (this->size == 1)
        {
            this-> head = this->tail = nullptr;
            this->size--;
        }
        else
        {
            Node<T>* temp = this->head;
            this->head = this->head->next;
            this->size--;
        }
    }
    else if (list_pos == this->size - 1)
    {
        if (this->size == 1)
        {
            this-> head = this->tail = nullptr;
            this->size--;
        }
        else
        {
            Node<T>* temp = this->tail;
            this->tail = this->tail->prev;
            this->size--;
        }
    }
    else if ((list_pos < (this->size) / 2))
    {
        Node<T>* _ptr = this->head;
        for (int i = 0; i < list_pos; ++i)
        {
            _ptr = _ptr->next;
        }
        _ptr->prev->next = _ptr->next;
        _ptr->next->prev = _ptr->prev;
        this->size--;
    }
    else if (list_pos < this->size)
    {
        Node<T>* _ptr = this->tail;
        for (int i = this->size - 1; i > list_pos; --i)
        {
            _ptr = _ptr->prev;
        }
        _ptr->prev->next = _ptr->next;
        _ptr->next->prev = _ptr->prev;
        this->size--;
    }
}

template<class T>
void List<T>::PopBack()
{
    if (this->size == 1)
    {
        delete this->head;
        this-> head = this->tail = nullptr;
        this->size--;
    }
    else
    {
        Node<T>* temp = this->tail;
        this->tail = this->tail->prev;
        delete temp;
        this->size--;
    }
}


template<class T>
List<T>& List<T>::operator=(const List<T>& another)
{
    this->size = another.size;
    for (int i = 0; i < this->size; i++)
    {
        this->PushBack(another[i]);
    }
    return *this;
}

template<class T>
Node<T>* List<T>::refReturn(int list_pos)
{
    if ((list_pos < (this->size) / 2) && (list_pos < this->size))
    {
        Node<T>* _ptr = this->head;
        for (int i = 0; i < list_pos; ++i)
        {
            _ptr = _ptr->next;
        }
        return _ptr;
    }
    else if (list_pos < this->size)
    {
        Node<T>* _ptr = this->tail;
        for (int i = this->size - 1; i > list_pos; --i)
        {
            _ptr = _ptr->prev;
        }
        return _ptr;
    }
}
#endif // LIST_H
