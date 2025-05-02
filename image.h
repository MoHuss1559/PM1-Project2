#ifndef IMAGE_H
#define IMAGE_H

#include "matrix.h"
#include <stdexcept>
#include <algorithm>
#include <cmath> // For std::floor

class Image : public Matrix<float> {
private:
    int channels;

public:
    // Constructor with dimension validation
    Image(size_t width, size_t height, int channels = 3)
        : Matrix<float>(height, width), channels(channels)
    {
        if (channels < 1 || channels > 4) {
            throw std::invalid_argument("Channel count must be between 1 and 4");
        }
    }

    // Getter for channels
    int getChannels() const { return channels; }

    // Improved Image Resize with bilinear interpolation (Extra Credit)
    Image resize(size_t new_width, size_t new_height) const {
        if (new_width == 0 || new_height == 0) {
            throw std::invalid_argument("New dimensions must be greater than 0");
        }

        Image result(new_width, new_height, channels);
        float x_ratio = static_cast<float>(getCols()) / new_width;
        float y_ratio = static_cast<float>(getRows()) / new_height;

        for (size_t y = 0; y < new_height; ++y) {
            for (size_t x = 0; x < new_width; ++x) {
                float gx = std::max(0.0f, std::floor(x * x_ratio));
                float gy = std::max(0.0f, std::floor(y * y_ratio));
                size_t x1 = static_cast<size_t>(gx);
                size_t y1 = static_cast<size_t>(gy);
                size_t x2 = std::min(x1 + 1, getCols() - 1);
                size_t y2 = std::min(y1 + 1, getRows() - 1);

                float dx = (x * x_ratio) - gx;
                float dy = (y * y_ratio) - gy;

                // Bilinear interpolation
                float a = (*this)[y1][x1] * (1 - dx) * (1 - dy);
                float b = (*this)[y1][x2] * dx * (1 - dy);
                float c = (*this)[y2][x1] * (1 - dx) * dy;
                float d = (*this)[y2][x2] * dx * dy;

                result[y][x] = std::clamp(a + b + c + d, 0.0f, 255.0f);
            }
        }
        return result;
    }

    // Image scaling with value clamping
    Image scale(float factor) const {
        Image result(getCols(), getRows(), channels);
        for (size_t i = 0; i < getRows(); ++i) {
            for (size_t j = 0; j < getCols(); ++j) {
                result[i][j] = std::clamp((*this)[i][j] * factor, 0.0f, 255.0f);
            }
        }
        return result;
    }

    // Image addition with bounds checking
    Image operator+(const Image& other) const {
        validateDimensions(other, "addition");
        Image result(getCols(), getRows(), channels);
        for (size_t i = 0; i < getRows(); ++i) {
            for (size_t j = 0; j < getCols(); ++j) {
                result[i][j] = std::clamp((*this)[i][j] + other[i][j], 0.0f, 255.0f);
            }
        }
        return result;
    }

    // Image subtraction with bounds checking
    Image operator-(const Image& other) const {
        validateDimensions(other, "subtraction");
        Image result(getCols(), getRows(), channels);
        for (size_t i = 0; i < getRows(); ++i) {
            for (size_t j = 0; j < getCols(); ++j) {
                result[i][j] = std::clamp((*this)[i][j] - other[i][j], 0.0f, 255.0f);
            }
        }
        return result;
    }

private:
    // Helper for dimension validation
    void validateDimensions(const Image& other, const std::string& op) const {
        if (getRows() != other.getRows() || getCols() != other.getCols()) {
            throw std::invalid_argument("Image dimensions must match for " + op);
        }
        if (channels != other.channels) {
            throw std::invalid_argument("Channel counts must match for " + op);
        }
    }
};

#endif // IMAGE_H
