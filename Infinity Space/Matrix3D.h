#ifndef MATRIX3D_H
#define MATRIX3D_H

#include <array>
#include <stdexcept>
#include <iostream>

class Matrix3D {
public:
    static const int SIZE = 3; // 3x3 matrix size
    using MatrixArray = std::array<std::array<float, SIZE>, SIZE>;

    Matrix3D() : data{ {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}} } {}
    Matrix3D(const MatrixArray& initData) : data(initData) {}

    Matrix3D operator+(const Matrix3D& other) const {
        MatrixArray result;
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                result[i][j] = data[i][j] + other.data[i][j];
            }
        }
        return Matrix3D(result);
    }

    Matrix3D operator-(const Matrix3D& other) const {
        MatrixArray result;
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                result[i][j] = data[i][j] - other.data[i][j];
            }
        }
        return Matrix3D(result);
    }

    Matrix3D operator*(const Matrix3D& other) const {
        MatrixArray result = { {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}} };
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                for (int k = 0; k < SIZE; ++k) {
                    result[i][j] += data[i][k] * other.data[k][j];
                }
            }
        }
        return Matrix3D(result);
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

#endif // MATRIX3D_H