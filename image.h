#ifndef IMAGE_H
#define IMAGE_H

#include "matrix.h"
#include <stdexcept>
#include <algorithm>
#include <vector>

class Image : public Matrix<float> {
private:
    int channels;

public:
    // Constructor with dimensions and channels (default RGB)
    Image(size_t width, size_t height, int channels = 3)
        : Matrix<float>(height, width), channels(channels)
    {
        if (channels < 1 || channels > 4) {
            throw std::invalid_argument("Channel count must be between 1 and 4");
        }
    }

    // Getter for channels
    int getChannels() const { return channels; }

    // Image scaling with value clamping (prevents overflow)
    Image scale(float factor) const {
        Image result(getCols(), getRows(), channels);
        for (size_t i = 0; i < getRows(); ++i) {
            for (size_t j = 0; j < getCols(); ++j) {
                // Clamp values between 0.0f and 255.0f (typical image range)
                result[i][j] = std::clamp((*this)[i][j] * factor, 0.0f, 255.0f);
            }
        }
        return result;
    }

    // Resize image EXTRA CREDIT
    Image resize(size_t new_width, size_t new_height) const {
        if (new_width == 0 || new_height == 0) {
            throw std::invalid_argument("New dimensions must be greater than 0");
        }

        Image result(new_width, new_height, channels);
        float x_ratio = static_cast<float>(getCols() - 1) / (new_width - 1);
        float y_ratio = static_cast<float>(getRows() - 1) / (new_height - 1);

        for (size_t i = 0; i < new_height; i++) {
            for (size_t j = 0; j < new_width; j++) {
                float x = j * x_ratio;
                float y = i * y_ratio;
                
                size_t x1 = static_cast<size_t>(x);
                size_t y1 = static_cast<size_t>(y);
                size_t x2 = std::min(x1 + 1, getCols() - 1);
                size_t y2 = std::min(y1 + 1, getRows() - 1);

                float x_diff = x - x1;
                float y_diff = y - y1;

                float a = (*this)[y1][x1] * (1 - x_diff) * (1 - y_diff);
                float b = (*this)[y1][x2] * x_diff * (1 - y_diff);
                float c = (*this)[y2][x1] * (1 - x_diff) * y_diff;
                float d = (*this)[y2][x2] * x_diff * y_diff;

                result[i][j] = std::clamp(a + b + c + d, 0.0f, 255.0f);
            }
        }

        return result;
    } //end of extra credit

    // Image addition with channel compatibility check
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

    // Image subtraction with channel compatibility check
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

    // Element-wise multiplication
    Image operator*(const Image& other) const {
        validateDimensions(other, "element-wise multiplication");
        Image result(getCols(), getRows(), channels);
        for (size_t i = 0; i < getRows(); ++i) {
            for (size_t j = 0; j < getCols(); ++j) {
                result[i][j] = std::clamp((*this)[i][j] * other[i][j], 0.0f, 255.0f);
            }
        }
        return result;
    }

private:
    // Helper function to validate image dimensions and channels
    void validateDimensions(const Image& other, const std::string& operation) const {
        if (getRows() != other.getRows() || getCols() != other.getCols()) {
            throw std::invalid_argument(
                "Image dimensions must match for " + operation
            );
        }
        if (channels != other.channels) {
            throw std::invalid_argument(
                "Channel counts must match for " + operation
            );
        }
    }
};

#endif // IMAGE_H
