#include <cstdint>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include "matrix.hpp"

size_t op_count = 0;

typedef uint16_t test_inner_t;

struct test_t {
    test_inner_t value;
    test_t(): value{0} {}
    test_t(test_inner_t x): value{x} {}
};

test_t operator* (const test_t& lhs, const test_t& rhs) {
    op_count++;
    return lhs.value * rhs.value;
}

test_t operator+ (const test_t& lhs, const test_t& rhs) {
    return lhs.value + rhs.value;
}

test_t operator- (const test_t& lhs, const test_t& rhs) {
    return lhs.value - rhs.value;
}

bool operator!= (const test_t& lhs, const test_t& rhs) {
    return lhs.value != rhs.value;
}

test_t& operator+= (test_t& lhs, const test_t& rhs) {
    lhs.value += rhs.value;
    return lhs;
}

std::ostream& operator<< (std::ostream& os, const test_t& obj) {
    return os << obj.value;
}

typedef matrix4x4_t<test_t> test_matrix_t;

test_matrix_t make_random_matrix() {
    test_matrix_t result;
    for(size_t y = 0; y < 4; ++y) {
        for(size_t x = 0; x < 4; ++x) {
            result.at(y, x) = rand();
        }
    }
    return result;
}

int main() {
    test_matrix_t A = make_random_matrix();
    std::cout << "A = \n" << A << std::endl;
    test_matrix_t B = make_random_matrix();
    std::cout << "B = \n" << B << std::endl;
    test_matrix_t C1;
    {
        op_count = 0;
        C1 = multiply4x4_naive(A, B);
        std::cout << "AB = \n" << C1 << std::endl;
        std::cout << "Naive: " << op_count << " scalar multiplications" << std::endl;
    }
    test_matrix_t C2;
    {
        op_count = 0;
        C2 = multiply4x4_winograd(A, B);
        std::cout << "AB = \n" << C2 << std::endl;
        std::cout << "Winograd: " << op_count << " scalar multiplications" << std::endl;
    }
    {
        std::cout << "Does Winograd match? " << (C1 == C2 ? "true" : "false") << std::endl;
    }
    return 0;
}