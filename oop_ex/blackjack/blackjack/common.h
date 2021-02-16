//
//  common.h
//  blackjack
//
//  Created by ChrisLam on 15/02/2021.
//

#ifndef common_h
#define common_h

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

#endif /* common_h */
