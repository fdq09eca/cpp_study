#pragma once

#define _CRT_SECURE_NO_WARNINGS 1

#include <string.h>
#include <iostream>
#include <stdio.h>

#define DUMP_VAR(X)                        \
    do                                     \
    {                                      \
        std::cout << #X ": " << X << "\n"; \
    } while (false)
//----------

inline size_t next_pow_of_two(size_t n) {
    size_t i = 1;
    while (i <  n) {
		i *= 2;
	}
    return i;
}

class NonCopyable {
public:
	NonCopyable() = default;
	NonCopyable(const NonCopyable& r) = delete;
	void operator=(const NonCopyable&) = delete;
};