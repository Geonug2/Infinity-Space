#ifndef MATRIX2D_H
#define MATRIX2D_H

#include <array>
#include <stdexcept>
#include <iostream>

class Matrix2D {
public:
    static const int SIZE = 2; // 2x2 matrix size
    using MatrixArray = std::array<std::array<float, SIZE>, SIZE>;

    Matrix2D() : data{ {{0, 0}, {0, 0}} } {}
    Matrix2D(const MatrixArray& initData) : data(initData) {}

    Matrix2D operator+(const Matrix2D& other) const {
        MatrixArray result;
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                result[i][j] = data[i][j] + other.data[i][j];
            }
        }
        return Matrix2D(result);
    }

    Matrix2D operator-(const Matrix2D& other) const {
        MatrixArray result;
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                result[i][j] = data[i][j] - other.data[i][j];
            }
        }
        return Matrix2D(result);
    }

    Matrix2D operator*(const Matrix2D& other) const {
        MatrixArray result = { {{0, 0}, {0, 0}} };
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                for (int k = 0; k < SIZE; ++k) {
                    result[i][j] += data[i][k] * other.data[k][j];
                }
            }
        }
        return Matrix2D(result);
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

#endif // MATRIX2D_H