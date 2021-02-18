//
//  main.cpp
//  blackjack
//
//  Created by ChrisLam on 14/02/2021.
//

#include <iostream>
#include "CardDeck.hpp"
#include "Game.hpp"
#include "common.h"
#define RUN_TEST(NAME) \
std::cout << "==TEST_" << #NAME << "==\n";     \
    void TEST_##NAME();                        \
    TEST_##NAME();                             \

//==

int main() {
    std::srand(static_cast<unsigned int>(time(NULL)));
    Game game;
    game.run();
//    TEST_Card();
//    RUN_TEST(CardDeck);
//    TEST_CardDeck_swap();
//    TEST_CardDeck_sort();
//    CardDeck_test();
    //    Card_test();
    return 0;
}
