//
//  common.hpp
//  Template-DynamicArray
//
//  Created by ChrisLam on 29/03/2021.
//

#ifndef common_hpp
#define common_hpp
#include <stdio.h>
#include <iostream>
#include <cfloat>

inline bool float_eq(float a, float b) {
    return fabs(a - b) < FLT_EPSILON;
}

inline int next_pow_of_two(const int n) {
    int    i =  1;
    while (i <  n)
           i *= 2;
    return i;
}
#endif /* common_hpp */
