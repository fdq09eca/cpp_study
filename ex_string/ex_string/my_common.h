//
//  my_common.h
//  ex_string
//
//  Created by ChrisLam on 12/02/2021.
//

#ifndef my_common_h
#define my_common_h

#define TEST(EXPR) \
    do {           \
        printf("[%s] Line %3d: %s\n", ((EXPR) ? " OK " : "FAIL"), __LINE__, #EXPR); \
    } while (0)                                                                     \
//-------------------

#define dump_var(X)                                     \
    do {                                                \
        std::cout << "dump_var: " #X ": " << X << "\n"; \
    } while (false)                                     \
//=====

inline size_t next_pow_of_two(size_t v) {
    size_t i = 1;
    while (i < v)
    {
        i *= 2;
    }
    return i;
}

#endif /* my_common_h */
