#ifndef MATRIX_H
#define MATRIX_H

#include "vector.h"
#include <iostream>
#include <stdexcept>

template <typename T>
class Matrix {
private:
    size_t rows, cols;
    Vector<Vector<T>> data;

public:
    Matrix(size_t rows, size_t cols) : rows(rows), cols(cols), data(rows) {
        for (size_t i = 0; i < rows; ++i)
            data[i] = Vector<T>(cols);
    }

    // Dimension accessors
    size_t getRows() const { return rows; }
    size_t getCols() const { return cols; }

    // Element access
    Vector<T>& operator[](size_t row) {
        if (row >= rows) throw std::out_of_range("Matrix row out of range");
        return data[row];
    }

    const Vector<T>& operator[](size_t row) const {
        if (row >= rows) throw std::out_of_range("Matrix row out of range");
        return data[row];
    }

    // Transpose (Fixed Implementation)
    Matrix transpose() const {
        Matrix result(cols, rows);
        for (size_t i = 0; i < rows; ++i)
            for (size_t j = 0; j < cols; ++j)
                result[j][i] = data[i][j];
        return result;
    }

    // Debug print
    void debugPrint(const std::string& label) const {
        std::cout << label << " (" << rows << "x" << cols << "):\n";
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j)
                std::cout << data[i][j] << " ";
            std::cout << "\n";
        }
    }
};

#endif // MATRIX_H
