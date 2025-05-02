#include <iostream>
#include "vector.h"
#include "matrix.h"
#include "image.h"

int main() {
    // Test Matrix Transpose
    Matrix<int> mat(2, 3);
    mat[0][0] = 1; mat[0][1] = 2; mat[0][2] = 3;
    mat[1][0] = 4; mat[1][1] = 5; mat[1][2] = 6;
    
    auto transposed = mat.transpose();
    mat.debugPrint("Original");
    transposed.debugPrint("Transposed");

    // Test Image Resize
    Image img(4, 4, 1); // Grayscale
    for (size_t i = 0; i < 4; ++i)
        for (size_t j = 0; j < 4; ++j)
            img[i][j] = static_cast<float>(i + j) * 25.0f;

    img.debugPrint("\nOriginal Image (4x4)");
    auto resized = img.resize(2, 2);
    resized.debugPrint("Resized Image (2x2)");

    return 0;
}
