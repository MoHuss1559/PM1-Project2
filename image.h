#ifndef IMAGE_H
#define IMAGE_H

#include "matrix.h"

class Image : public Matrix<float> {
private:
    int channels;

public:
    // Constructor
    Image(size_t width, size_t height, int channels = 3) 
        : Matrix<float>(height, width), channels(channels) {}

    // Getter for channels
    int getChannels() const { return channels; }

    // Image scaling
    Image scale(float factor) const {
        Image result(getCols(), getRows(), channels);
        for (size_t i = 0; i < getRows(); ++i)
            for (size_t j = 0; j < getCols(); ++j)
                result[i][j] = (*this)[i][j] * factor;
        return result;
    }

    // Image addition (checks channel compatibility)
    Image operator+(const Image& other) const {
        if (channels != other.channels)
            throw std::invalid_argument("Image channels must match for addition!");
        Image result(getCols(), getRows(), channels);
        for (size_t i = 0; i < getRows(); ++i)
            for (size_t j = 0; j < getCols(); ++j)
                result[i][j] = (*this)[i][j] + other[i][j];
        return result;
    }

    // Image subtraction
    Image operator-(const Image& other) const {
        if (channels != other.channels)
            throw std::invalid_argument("Image channels must match for subtraction!");
        Image result(getCols(), getRows(), channels);
        for (size_t i = 0; i < getRows(); ++i)
            for (size_t j = 0; j < getCols(); ++j)
                result[i][j] = (*this)[i][j] - other[i][j];
        return result;
    }
};

#endif // IMAGE_H









//Andrew's version of image

#ifndef IMAGEHEADER_H
#define IMAGEHEADER_H

#include <iostream>
#include "matrixheader.h"

template <typename T>
class Image : public Matrix<T> {
public:
    // Inherit constructors
    using Matrix<T>::Matrix;

    // Scale the image by a scalar
    void scale(T scalar) {
        for (int i = 0; i < this->numRows(); ++i) {
            for (int j = 0; j < this->numCols(); ++j) {
                this->at(i, j) *= scalar;
            }
        }
    }

    // Element-wise addition
    Image<T> operator+(const Image<T>& other) const {
        Matrix<T> result = Matrix<T>::operator+(other);
        return static_cast<Image<T>>(result);
    }

    // Element-wise subtraction
    Image<T> operator-(const Image<T>& other) const {
        Matrix<T> result = Matrix<T>::operator-(other);
        return static_cast<Image<T>>(result);
    }

    // Scalar multiplication
    Image<T> operator*(T scalar) const {
        Matrix<T> result = Matrix<T>::operator*(scalar);
        return static_cast<Image<T>>(result);
    }

    // Element-wise multiplication
    Image<T> multiply(const Image<T>& other) const {
        if (this->numRows() != other.numRows() || this->numCols() != other.numCols()) {
            std::cerr << "Error: Image dimensions do not match for element-wise multiplication." << std::endl;
            exit(1);
        }

        Image<T> result(this->numRows(), this->numCols());
        for (int i = 0; i < this->numRows(); ++i) {
            for (int j = 0; j < this->numCols(); ++j) {
                result.at(i, j) = this->at(i, j) * other.at(i, j);
            }
        }
        return result;
    }

    void resize(int newRows, int newCols) {
        if constexpr (!std::is_same<T, unsigned char>::value) {
            std::cerr << "Resize only supports unsigned char pixel types.\n";
            return;
        }
    
        int oldRows = this->numRows();
        int oldCols = this->numCols();
    
        // Flatten original data
        std::vector<unsigned char> input(oldRows * oldCols);
        for (int i = 0; i < oldRows; ++i)
            for (int j = 0; j < oldCols; ++j)
                input[i * oldCols + j] = this->at(i, j);
    
        // Prepare output buffer
        std::vector<unsigned char> output(newRows * newCols);
    
        // Resize using stb
        int success = stbir_resize_uint8(
            input.data(), oldCols, oldRows, 0,
            output.data(), newCols, newRows, 0, 1
        );
    
        if (!success) {
            std::cerr << "Resize failed.\n";
            return;
        }
    
        // Replace internal data
        *this = Image<T>(newRows, newCols);
        for (int i = 0; i < newRows; ++i)
            for (int j = 0; j < newCols; ++j)
                this->at(i, j) = output[i * newCols + j];
    }
    
};

#endif // IMAGEHEADER_H
