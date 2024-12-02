#ifndef MATRIX4D_H
#define MATRIX4D_H

#include <array>
#include <stdexcept>
#include <iostream>

class Matrix4D {
public:
    static const int SIZE = 4; // 4x4 matrix size
    using MatrixArray = std::array<std::array<float, SIZE>, SIZE>;

    Matrix4D() : data{ {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}} } {}
    Matrix4D(const MatrixArray& initData) : data(initData) {}

    Matrix4D operator+(const Matrix4D& other) const {
        MatrixArray result;
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                result[i][j] = data[i][j] + other.data[i][j];
            }
        }
        return Matrix4D(result);
    }

    Matrix4D operator-(const Matrix4D& other) const {
        MatrixArray result;
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                result[i][j] = data[i][j] - other.data[i][j];
            }
        }
        return Matrix4D(result);
    }

    Matrix4D operator*(const Matrix4D& other) const {
        MatrixArray result = { {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}} };
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                for (int k = 0; k < SIZE; ++k) {
                    result[i][j] += data[i][k] * other.data[k][j];
                }
            }
        }
        return Matrix4D(result);
    }

    void Print() const {
        for (const auto& row : data) {
            for (const auto& elem : row) {
                std::cout << elem << " ";
            }
            std::cout << std::endl;
        }
    }

private:
    MatrixArray data;
};

#endif // MATRIX4D_H