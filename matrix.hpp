#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <array>
#include <iostream>

template <typename T> struct matrix4x4_t {
    // 4x4 matrix in row-major order
    std::array<T, 16> data;
    T& at(size_t y, size_t x) {
        return data[y*4+x];
    }
    const T& at(size_t y, size_t x) const {
        return data[y*4+x];
    }
};

template <typename T> bool operator==(const matrix4x4_t<T> lhs, const matrix4x4_t<T> rhs) {
    for(size_t y = 0; y < 4; ++y) {
        for(size_t x = 0; x < 4; ++x) {
            if(lhs.at(y,x) != rhs.at(y,x)) {
                return false;
            }
        }
    }
    return true;
}

template <typename T> std::ostream& operator<<(std::ostream& os, const matrix4x4_t<T>& mat) {
    for(size_t y = 0; y < 4; ++y) {
        os << (y == 0 ? "[" : " ");
        for(size_t x = 0; x < 4; ++x) {
            if(x != 0) {
                os << "\t";
            }
            os << mat.at(y,x);
        }
        os << (y == 3 ? "]" : "\n");
    }
    return os;
}

template <typename T> matrix4x4_t<T> multiply4x4_naive(const matrix4x4_t<T>& A, const matrix4x4_t<T> B) {
    matrix4x4_t<T> result;

    for(size_t i = 0; i < 4; ++i) {
        for(size_t j = 0; j < 4; ++j) {
            T entry = 0;
            for(size_t k = 0; k < 4; ++k) {
                entry += A.at(i, k) * B.at(k, j);
            }
            result.at(i,j) = entry;
        }
    }

    return result;
};

template <typename T> matrix4x4_t<T> multiply4x4_winograd(const matrix4x4_t<T>& A, const matrix4x4_t<T>& B) {
    matrix4x4_t<T> result;
    std::array<T, 4> A_aus;
    std::array<T, 4> B_aus;

    for (size_t i = 0; i < 4; ++i) {
        A_aus[i] = A.at(i,0) * A.at(i,1) + A.at(i,2) * A.at(i,3);
    }

    for (size_t j = 0; j < 4; ++j) {
        B_aus[j] = B.at(0,j) * B.at(1,j) + B.at(2,j) * B.at(3,j);
    }

    for (size_t i = 0; i < 4; ++i) {
        for (size_t j = 0; j < 4; ++j) {
            result.at(i,j) =
                (A.at(i,0) + B.at(1,j)) * (A.at(i,1) + B.at(0,j)) +
                (A.at(i,2) + B.at(3,j)) * (A.at(i,3) + B.at(2,j)) -
                A_aus[i] - B_aus[j];
        }
    }

    return result;
}


#endif