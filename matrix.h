#ifndef MATRIXHEADER_H
#define MATRIXHEADER_H

#include <iostream>
#include <vector>
#include "vectorheader.h"

template <typename T>
class Matrix {
private:
    int rows, cols;
    std::vector<Vector<T>> data;

public:
    // Constructor for Matrix
    Matrix(int rows, int cols) : rows(rows), cols(cols), data(rows, Vector<T>(cols)) {}

    // Accessor for matrix element 
    T& at(int row, int col) {
        if (row < 0 || row >= rows || col < 0 || col >= cols) {
            std::cout << "Error: Matrix indices out of bounds!" << std::endl;
            exit(1);
        }
        return data[row].at(col);
    }

    // Accessor for matrix element (const version)
    const T& at(int row, int col) const {
        if (row < 0 || row >= rows || col < 0 || col >= cols) {
            std::cout << "Error: Matrix indices out of bounds!" << std::endl;
            exit(1);
        }
        return data[row].at(col); 
    }

    // Print the matrix
    void print() const {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                std::cout << data[i].at(j) << " ";
            }
            std::cout << std::endl;
        }
    }

    // Operator overloading for addition (Matrix + Matrix)
    Matrix<T> operator+(const Matrix<T>& other) const {
        if (this->rows != other.rows || this->cols != other.cols) {
            std::cout << "Error: Matrices dimensions do not match for addition!" << std::endl;
            exit(1);
        }
        Matrix<T> result(rows, cols);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                result.at(i, j) = this->at(i, j) + other.at(i, j);
            }
        }
        return result;
    }

    // Operator overloading for subtraction (Matrix - Matrix)
    Matrix<T> operator-(const Matrix<T>& other) const {
        if (this->rows != other.rows || this->cols != other.cols) {
            std::cout << "Error: Matrices dimensions do not match for subtraction!" << std::endl;
            exit(1);
        }
        Matrix<T> result(rows, cols);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                result.at(i, j) = this->at(i, j) - other.at(i, j);
            }
        }
        return result;
    }

    // Operator overloading for scalar multiplication (Matrix * scalar)
    Matrix<T> operator*(T scalar) const {
        Matrix<T> result(rows, cols);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                result.at(i, j) = this->at(i, j) * scalar;
            }
        }
        return result;
    }

    int numRows() const { return rows; }
    int numCols() const { return cols; }

    // Transpose EXTRA CREDIT*******************
Matrix<T> transpose() const {
    Matrix<T> result(this->cols, this->rows);
    for (int i = 0; i < this->rows; ++i) {
        for (int j = 0; j < this->cols; ++j) {
            result.at(j, i) = this->at(i, j);
        }
    }
    return result;
}

};

#endif
