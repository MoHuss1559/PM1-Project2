#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <stdexcept> // For std::out_of_range

template <typename T>
class Vector {
private:
    size_t length;
    T* data;

public:
    // Constructor
    explicit Vector(size_t size = 0) : length(size), data(new T[size]()) {}

    // Destructor
    ~Vector() { delete[] data; }

    // Copy Constructor
    Vector(const Vector& other) : length(other.length), data(new T[other.length]) {
        for (size_t i = 0; i < length; ++i)
            data[i] = other.data[i];
    }

    // Copy Assignment
    Vector& operator=(const Vector& other) {
        if (this != &other) {
            delete[] data;
            length = other.length;
            data = new T[length];
            for (size_t i = 0; i < length; ++i)
                data[i] = other.data[i];
        }
        return *this;
    }

    // Accessors (with bounds checking)
    T& operator[](size_t index) {
        if (index >= length) throw std::out_of_range("Vector index out of range!");
        return data[index];
    }

    const T& operator[](size_t index) const {
        if (index >= length) throw std::out_of_range("Vector index out of range!");
        return data[index];
    }

    // Size query
    size_t size() const { return length; }

    // Arithmetic operations
    Vector operator+(const Vector& other) const {
        if (length != other.length)
            throw std::invalid_argument("Vector sizes must match for addition!");
        Vector result(length);
        for (size_t i = 0; i < length; ++i)
            result[i] = data[i] + other[i];
        return result;
    }

    Vector operator-(const Vector& other) const {
        if (length != other.length)
            throw std::invalid_argument("Vector sizes must match for subtraction!");
        Vector result(length);
        for (size_t i = 0; i < length; ++i)
            result[i] = data[i] - other[i];
        return result;
    }

    // Scalar multiplication
    Vector operator*(T scalar) const {
        Vector result(length);
        for (size_t i = 0; i < length; ++i)
            result[i] = data[i] * scalar;
        return result;
    }
};

#endif // VECTOR_H
