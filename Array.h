
#pragma once
#include <iostream>

template<typename T>
class Array {
private:
    T* _base;
    T* _top;
    int _size;

public:
    Array(int n);
    ~Array();
    Array(const Array& arr) = default;
    Array& operator=(const Array& arr) = default;

    int size() const;
    void push(const T& t);
    T& operator[](int i);
    void print() const;

    class OutOfRange {};
};

template<typename T>
Array<T>::Array(int n): _base(new T[n]), _top(_base), _size(n) {}

template<typename T>
int Array<T>::size() const { return _top - _base; }

template<typename T>
void Array<T>::push(const T &t) { *_top++ = t; }

template<typename T>
T &Array<T>::operator[](int i)
{
    if (i < 0 || _size <= i)
    {
        throw OutOfRange();
    }
    return _base[i];
}

template<typename T>
Array<T>::~Array() {
    delete[] _base; 
}

template<typename T>
void Array<T>::print() const
{
    for (int i = 0; i < size(); ++i)
    {
        std::cout << _base[i] << " ";
    }
    std::cout << std::endl;
}
