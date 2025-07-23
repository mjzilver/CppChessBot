#pragma once
#include <cstdint>
#include <cassert>

// Basically the same as __builtin_ctzll
constexpr unsigned int ctz(uint64_t x) {
    assert(x != 0 && "ctz called with zero");

    unsigned int n = 0;
    while ((x & 1) == 0) {
        x >>= 1;
        n++;
    }
    return n;
}