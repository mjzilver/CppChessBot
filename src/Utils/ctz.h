#pragma once
#include <cstdint>
#include <stdexcept>

// Basically the same as __builtin_ctzll
constexpr unsigned int ctz(uint64_t x) {
    if (x == 0) {
        throw std::invalid_argument("Input to ctz cannot be zero.");
    }
    int n = 0;
    while ((x & 1) == 0) {
        x >>= 1;
        n++;
    }
    return n;
}