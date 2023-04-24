
#pragma once
#include <iostream>

template<class T>
class Array {
private:
    T* _base;
    T* _top;
    int _max_size;

public:
    Array(int n);
    Array(const Array& arr);
    Array& operator=(const Array& arr);
    ~Array();

    int size() const;
    void push(const T& t);
    T& operator[](int i);
    const T& operator[](int i) const;

    class OutOfRange {};
};

template <class S>
std::ostream& operator<<(std::ostream& os, const Array<S>& arr);

template<class T>
Array<T>::Array(int n):
    _base(new T[n]),
    _top(_base),
    _max_size(n) {}

template<class T>
Array<T>::Array(const Array& arr):
    _base(new T[arr._max_size]),
    _top(_base),
    _max_size(arr._max_size) {}

template<class T>
Array<T> &Array<T>::operator=(const Array& arr) {
    if (this == &arr) {
        return *this;
    }

    T *temp = new T[arr._max_size];
    for (int i = 0; i < arr.size(); i++) {
        temp[i] = arr._base[i];
    }
    delete[] _base;
    _base = temp;
    _top = _base + arr.size();
    _max_size = arr._max_size;
    return *this;
}

template<class T>
Array<T>::~Array() {
    delete[] _base;
}

template<class T>
int Array<T>::size() const {
    return _top - _base;
}

template<class T>
void Array<T>::push(const T &t) {
    if (size() == _max_size) {
        throw OutOfRange();
    }
    *_top++ = t;
}

template<class T>
T &Array<T>::operator[](int i) {
    if (i < 0 || size() <= i) {
        throw OutOfRange();
    }
    return _base[i];
}

template<class T>
const T &Array<T>::operator[](int i) const {
    if (i < 0 || size() <= i) {
        throw OutOfRange();
    }
    return _base[i];
}

template<class S>
std::ostream& operator<<(std::ostream& os, const Array<S>& arr) {
    for (int i = 0; i < arr.size(); ++i) {
        os << arr[i] << " ";
    }
    return os;
}