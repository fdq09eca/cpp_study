//
//  main.cpp
//  blackjack
//
//  Created by ChrisLam on 14/02/2021.
//

#include <iostream>
#include "CardDeck.hpp"
#include "common.h"

void CardDeck_test() {
    CardDeck d;
    dump_var(d);
    TEST(d.card_cap() == 52);
    
    for (size_t idx = 0; idx < 52; idx++) {
        Card rm_card = d.remove(0);
        dump_var(rm_card);
        TEST(d.count_card() == 52 - idx - 1);
    }
    
    
    
}

int main() {
    CardDeck_test();
    return 0;
}
