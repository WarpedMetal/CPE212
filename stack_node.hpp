#ifndef STACK_HPP
#define STACK_HPP

#include <iostream>
#include <string>
#include <string.h>

#define STACK_ALLOCATED_BLOCK 0x10

template<typename Data>
struct StackNode
{
    Data data;
    StackNode<Data> * next;
    StackNode<Data> * prev;

    StackNode(const Data & data)
    {
        this->data = data;
    }
};

template<typename Data>
class Stack
{
private:
    StackNode<Data> * _lastNode;



public:
    explicit Stack();
    ~Stack();

    Stack(const Stack<Data> & other) = delete;
    Stack& operator=(const Stack<Data> & other) = delete;
    Stack(Stack<Data> && other);
    Stack& operator=(Stack<Data> && other);

    void AddItem(const Data & data);
    Data PopItem();
    bool IsEmpty() const;
    unsigned int Length() const ;
};


template<typename Data>
Stack<Data>::Stack()
{
    std::cout << "Stack() called" << std::endl;
    _dataPtr = new Data[_allocated];
}

template<typename Data>
Stack<Data>::~Stack()
{
    std::cout << "Stack<Data>::~Stack()" << std::endl;
    delete []_dataPtr;
}

template<typename Data>
Stack<Data>::Stack(Stack<Data> && other)
{
    std::cout << "MOVE Ctr called" << std::endl;
    while(!other.IsEmpty())
    {
        AddItem(other.PopItem());
    }
}

template<typename Data>
Stack<Data>& Stack<Data>::operator=(Stack<Data> && other)
{
    std::cout << "move operator= called" << std::endl;
    while(!other.IsEmpty())
    {
        AddItem(other.PopItem());
    }
    return *this;
}


template<typename Data>
void Stack<Data>::AddItem(const Data & data)
{
    std::cout << "Adding Item: " << data << std::endl;
    StackNode<Data> *newItem = new StackNode<Data>(data);
    newItem->prev = _lastNode;
    _lastNode->next = newItem;
    _lastNOde = newItem;
}

template<typename Data>
Data Stack<Data>::PopItem()
{
    std::cout << "Count: " << _count << std::endl;
    std::cout << "val: " << _dataPtr[_count] << std::endl;
    
}

template<typename Data>
bool Stack<Data>::IsEmpty() const
{
    return _count == 0;
}

template<typename Data>
unsigned int Stack<Data>::Length() const
{
    return _count;
}

template<typename Data>
void Stack<Data>::reallocate()
{
    std::cout << "stack::reallocate()" << std::endl;
    _allocated += STACK_ALLOCATED_BLOCK;
    Data * tmpList = new Data[_allocated];
    
    for(int i = 0; i < _count; i ++)
    {
        tmpList[i] = _dataPtr[i];
    }

    delete _dataPtr;
    _dataPtr = tmpList;
}



#endif