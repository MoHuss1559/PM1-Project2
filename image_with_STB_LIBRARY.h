#ifndef IMAGEHEADER_H
#define IMAGEHEADER_H

#include "matrixheader.h"
#include <vector>
#include <stdexcept>

#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "stb_image_resize.h"

// Generic Image class template
template <typename T>
class Image : public Matrix<T> {
public:
    using Matrix<T>::Matrix;

    void scale(T scalar) {
        for (int i = 0; i < this->numRows(); ++i) {
            for (int j = 0; j < this->numCols(); ++j) {
                this->at(i, j) *= scalar;
            }
        }
    }

    Image<T> operator+(const Image<T>& other) const {
        Matrix<T> result = Matrix<T>::operator+(other);
        return static_cast<Image<T>>(result);
    }

    Image<T> operator-(const Image<T>& other) const {
        Matrix<T> result = Matrix<T>::operator-(other);
        return static_cast<Image<T>>(result);
    }

    Image<T> operator*(T scalar) const {
        Matrix<T> result = Matrix<T>::operator*(scalar);
        return static_cast<Image<T>>(result);
    }

    Image<T> multiply(const Image<T>& other) const {
        if (this->numRows() != other.numRows() || this->numCols() != other.numCols()) {
            std::cerr << "Error: Image dimensions do not match for multiplication.\n";
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
};

// Specialization for unsigned char with RGB resizing
template <>
class Image<unsigned char> : public Matrix<unsigned char> {
private:
    int channels;

public:
    using Matrix<unsigned char>::Matrix;

    Image(int height, int width, int channels = 3)
        : Matrix<unsigned char>(height, width * channels), channels(channels) {}

    int getChannels() const { return channels; }

    // Resize function using stb_image_resize EXTRA CREDIT
    Image<unsigned char> resize(int new_width, int new_height) const {
        int old_width = this->numCols() / channels;
        int old_height = this->numRows();

        // Buffer to hold original image data
        std::vector<unsigned char> inputBuffer(this->numRows() * this->numCols());
        // Buffer to hold resized image data
        std::vector<unsigned char> outputBuffer(new_width * new_height * channels);

        // Copy current image data into the input buffer (interleaved RGB format)
        for (int i = 0; i < this->numRows(); ++i) {
            for (int j = 0; j < this->numCols(); ++j) {
                inputBuffer[i * this->numCols() + j] = this->at(i, j);
            }
        }

        // Use stb_image_resize to resize the image
        stbir_resize_uint8(
            inputBuffer.data(), old_width, old_height, 0, 
            outputBuffer.data(), new_width, new_height, 0, 
            channels
        );

        // Create the result image with the resized data
        Image<unsigned char> result(new_height, new_width, channels);
        for (int i = 0; i < new_height; ++i) {
            for (int j = 0; j < new_width * channels; ++j) {
                result.at(i, j) = outputBuffer[i * new_width * channels + j];
            }
        }

        return result;
    }
};

#endif // IMAGEHEADER_H
