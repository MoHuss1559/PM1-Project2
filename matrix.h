#ifndef MATRIX_H
#define MATRIX_H

#include "vector.h"
#include <iostream>

template <typename T>
class Matrix {
private:
    size_t rows, cols;
    Vector<Vector<T>> data;

public:
    // Constructor
    Matrix(size_t rows, size_t cols) : rows(rows), cols(cols), data(rows) {
        for (size_t i = 0; i < rows; ++i)
            data[i] = Vector<T>(cols);
    }

    // Size getters
    size_t getRows() const { return rows; }
    size_t getCols() const { return cols; }

    // Accessors (with bounds checking)
    Vector<T>& operator[](size_t row) {
        if (row >= rows) throw std::out_of_range("Matrix row out of range!");
        return data[row];
    }

    const Vector<T>& operator[](size_t row) const {
        if (row >= rows) throw std::out_of_range("Matrix row out of range!");
        return data[row];
    }

    // Matrix addition
    Matrix operator+(const Matrix& other) const {
        if (rows != other.rows || cols != other.cols)
            throw std::invalid_argument("Matrix dimensions must match for addition!");
        Matrix result(rows, cols);
        for (size_t i = 0; i < rows; ++i)
            for (size_t j = 0; j < cols; ++j)
                result[i][j] = data[i][j] + other[i][j];
        return result;
    }

    // Matrix subtraction
    Matrix operator-(const Matrix& other) const {
        if (rows != other.rows || cols != other.cols)
            throw std::invalid_argument("Matrix dimensions must match for subtraction!");
        Matrix result(rows, cols);
        for (size_t i = 0; i < rows; ++i)
            for (size_t j = 0; j < cols; ++j)
                result[i][j] = data[i][j] - other[i][j];
        return result;
    }

    // Scalar multiplication
    Matrix operator*(T scalar) const {
        Matrix result(rows, cols);
        for (size_t i = 0; i < rows; ++i)
            for (size_t j = 0; j < cols; ++j)
                result[i][j] = data[i][j] * scalar;
        return result;
    }

    // Matrix multiplication
    Matrix operator*(const Matrix& other) const {
        if (cols != other.rows)
            throw std::invalid_argument("Matrix dimensions incompatible for multiplication!");
        Matrix result(rows, other.cols);
        for (size_t i = 0; i < rows; ++i)
            for (size_t j = 0; j < other.cols; ++j)
                for (size_t k = 0; k < cols; ++k)
                    result[i][j] += data[i][k] * other[k][j];
        return result;
    }

    // Transpose (Extra Credit)
    Matrix transpose() const {
        Matrix result(cols, rows);
        for (size_t i = 0; i < rows; ++i)
            for (size_t j = 0; j < cols; ++j)
                result[j][i] = data[i][j];
        return result;
    }

    // Print matrix (for debugging)
    void print() const {
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j)
                std::cout << data[i][j] << " ";
            std::cout << "\n";
        }
    }
};

#endif // MATRIX_H
