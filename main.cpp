#include <iostream>
#include "vector.h"
#include "matrix.h"
#include "image.h"

int main() {
    // ===== Vector Testing =====
    std::cout << "=== Testing Vector ===" << std::endl;
    Vector<int> vec1(3);
    vec1[0] = 1; vec1[1] = 2; vec1[2] = 3;
    Vector<int> vec2 = vec1 * 2;
    std::cout << "Vector1: " << vec1[0] << " " << vec1[1] << " " << vec1[2] << std::endl;
    std::cout << "Vector2 (scaled): " << vec2[0] << " " << vec2[1] << " " << vec2[2] << std::endl;

    // ===== Matrix Testing =====
    std::cout << "\n=== Testing Matrix ===" << std::endl;
    Matrix<int> mat1(2, 2);
    mat1[0][0] = 1; mat1[0][1] = 2;
    mat1[1][0] = 3; mat1[1][1] = 4;
    Matrix<int> mat2 = mat1 * 2;
    std::cout << "Matrix1:\n";
    mat1.print();
    std::cout << "Matrix2 (scaled):\n";
    mat2.print();

    // ===== Image Testing =====
    std::cout << "\n=== Testing Image ===" << std::endl;
    Image img1(2, 2, 3); // 2x2 RGB image
    img1[0][0] = 100.0f; img1[0][1] = 150.0f;
    img1[1][0] = 200.0f; img1[1][1] = 250.0f;
    Image img2 = img1.scale(0.5f);
    std::cout << "Image1[0][0]: " << img1[0][0] << std::endl;
    std::cout << "Image2 (scaled)[0][0]: " << img2[0][0] << std::endl;

    return 0;
}
