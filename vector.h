#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <cassert>

template <typename T>
class Vector {
private:
    int length;
    T* data;
public:
    // Constructor
    Vector(int size) : length(size), data(new T[size]) {}

    // Copy constructor
    Vector(const Vector<T>& other) : length(other.length), data(new T[other.length]) {
        for (int i = 0; i < length; ++i) {
            data[i] = other.data[i];
        }
    }

    // Copy assignment operator
    Vector<T>& operator=(const Vector<T>& other) {
        if (this != &other) {
            delete[] data;
            length = other.length;
            data = new T[length];
            for (int i = 0; i < length; ++i) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    // Destructor
    ~Vector() { delete[] data; }

    // Accessors
    T& operator[](int index) {
        assert(index >= 0 && index < length);
        return data[index];
    }

    const T& operator[](int index) const {
        assert(index >= 0 && index < length);
        return data[index];
    }

    T& at(int index) {
        assert(index >= 0 && index < length);
        return data[index];
    }

    const T& at(int index) const {
        assert(index >= 0 && index < length);
        return data[index];
    }

    int size() const { return length; }

    // Addition
    Vector<T> operator+(const Vector<T>& other) const {
        assert(length == other.length);
        Vector<T> result(length);
        for (int i = 0; i < length; ++i) {
            result[i] = data[i] + other[i];
        }
        return result;
    }

    // Subtraction
    Vector<T> operator-(const Vector<T>& other) const {
        assert(length == other.length);
        Vector<T> result(length);
        for (int i = 0; i < length; ++i) {
            result[i] = data[i] - other[i];
        }
        return result;
    }
};

#endif // VECTOR_H
