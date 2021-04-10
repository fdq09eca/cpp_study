//
//  common.hpp
//  Heap
//
//  Created by ChrisLam on 10/04/2021.
//

#pragma once
#include <iostream>
  

#define TEST(EXPR)                                                                  \
    do                                                                              \
    {                                                                               \
        printf("[%s] Line %3d: %s\n", ((EXPR) ? " OK " : "FAIL"), __LINE__, #EXPR); \
    } while (0) //-------------------

#define dump_var(X)                        \
    do                                     \
    {                                      \
        std::cout << #X ": " << X << "\n"; \
    } while (false)


inline int next_pow_of_two(int v){
    int i = 1;
    while (i < v) i *= 2;
    return i;
}
