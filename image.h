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
