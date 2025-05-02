#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <stdexcept>
#include <algorithm>

template <typename T>
class Vector {
private:
    size_t length;
    T* data;

public:
    // Constructor
    explicit Vector(size_t size = 0) : length(size), data(size ? new T[size]() : nullptr) {}

    // Destructor
    ~Vector() { delete[] data; }

    // Copy Constructor
    Vector(const Vector& other) : length(other.length), data(other.length ? new T[other.length] : nullptr) {
        for (size_t i = 0; i < length; ++i)
            data[i] = other.data[i];
    }

    // Move Constructor
    Vector(Vector&& other) noexcept : length(other.length), data(other.data) {
        other.length = 0;
        other.data = nullptr;
    }

    // Copy Assignment
    Vector& operator=(const Vector& other) {
        if (this != &other) {
            delete[] data;
            length = other.length;
            data = length ? new T[length] : nullptr;
            for (size_t i = 0; i < length; ++i)
                data[i] = other.data[i];
        }
        return *this;
    }

    // Move Assignment
    Vector& operator=(Vector&& other) noexcept {
        if (this != &other) {
            delete[] data;
            length = other.length;
            data = other.data;
            other.length = 0;
            other.data = nullptr;
        }
        return *this;
    }

    // Accessors
    T& operator[](size_t index) {
        if (index >= length) throw std::out_of_range("Vector index out of range");
        return data[index];
    }

    const T& operator[](size_t index) const {
        if (index >= length) throw std::out_of_range("Vector index out of range");
        return data[index];
    }

    // Size query
    size_t size() const { return length; }

    // Clear memory
    void clear() {
        delete[] data;
        data = nullptr;
        length = 0;
    }
};

#endif // VECTOR_H
