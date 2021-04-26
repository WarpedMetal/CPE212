#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cstring>



template<typename Data>
class Vector
{
private:

    const int AllocatedCount = 0x10;

    Data * _dataPtr;
    int _allocated = AllocatedCount;
    int _count = 0;

    void reallocate()
    {
        if(_count < _allocated)
        {
            return;
        }

        int allocatedBefore = _allocated;
        _allocated += AllocatedCount;

        Data * tmp = new Data[_allocated];

        memcpy(tmp, _dataPtr, sizeof(Data) * allocatedBefore);
        delete [] _dataPtr;

        _dataPtr = tmp;
    }


public:

    Vector()
    {
        _dataPtr = new Data[_allocated];
    }

    ~Vector()
    {
        delete [] _dataPtr;
    }


    Vector(const Vector<Data> & other)
    {
        delete [] _dataPtr;
        _allocated = other._allocated;
        _count = other._count;

        _dataPtr = new Data[_allocated];
        memcpy(_dataPtr, other._dataPtr, sizeof(Data) * _count);
    }


    Vector<Data> & operator=(const Vector<Data> & other)
    {
        delete[] _dataPtr;
        _allocated = other._allocated;
        _count = other._count;

        _dataPtr = new Data[_allocated];
        memcpy(_dataPtr, other._dataPtr,  sizeof(Data) * _count);

        return * this;
    }

    void Insert(const Data & other)
    {
        reallocate();

        _dataPtr[_count++] = other;
    }

    void Delete(const Data & other)
    {
        for(int i = 0; i < _count; i ++)
        {
            if(_dataPtr[i] == other)
            {
                _dataPtr[i] = _dataPtr[_count - 1];
                _count --;
            }
        }
    }

    // gets the total amount of data in our Vector
    int Count() const
    {
        return _count;
    }

    // allows the access to the data within Vector via the 
    // [] operator.  NOTE THERE ARE NO BOUNDS CHECKS HERE
    Data & At(int index) const
    {
        return _dataPtr[index];
    }
};


#endif // VECTOR_HPP