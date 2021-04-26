#ifndef STACK_HPP
#define STACK_HPP

#include <stdexcept>

#define STACK_ALLOCATED_BLOCK 0x10



template<typename Data>
class Stack
{
private:
    Data * _dataPtr;
    unsigned int _allocated = STACK_ALLOCATED_BLOCK;
    unsigned int _count = 0;

    void reallocate();

public:

    Stack();
    ~Stack();

    void AddItem(const Data & data);
    Data PopItem();
    bool IsEmpty() const;
};


template<typename Data>
Stack<Data>::Stack()
{
    _dataPtr = new Data[_allocated];
}

template<typename Data>
Stack<Data>::~Stack()
{
    delete []_dataPtr;
}

template<typename Data>
void Stack<Data>::AddItem(const Data & data)
{
    if(_count == _allocated)
    {
        reallocate();
    }
    _dataPtr[_count++] = data;
}

template<typename Data>
Data Stack<Data>::PopItem()
{
    _count --;
    if(_count < 0)
    {
        throw new std::range_error("out of bounds error");
    }
    return _dataPtr[_count];
}

template<typename Data>
bool Stack<Data>::IsEmpty() const
{
    return _count == 0;
}

template<typename Data>
void Stack<Data>::reallocate()
{
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