//
//  Hand.cpp
//  blackjack
//
//  Created by ChrisLam on 17/02/2021.
//

#include "Hand.hpp"
#include "Card.hpp"

Hand::~Hand() {
    _card_count = 0;
}

void Hand::add(const Card& card) {
    if (_card_count >= MAX_CARD){
        assert(false);
        return;
    }
    _cards[_card_count] = card;
    _card_count++;
}

int Hand::point() const {
    int sum = 0;
    int n_ace = 0;
    for (size_t i = 0; i < _card_count; i++) {
        const int r = rank_to_int(_cards[i].rank());
        if (r == 1){
            n_ace++;
            sum += 11;
        } else if (r > 10) {
            sum += 10;
        } else {
            sum += r;
        }
    }
    
    
    if (sum > 21) {
        int diff =  sum - 21;
        int deduct_ace = (diff + 9) / 10;
        if  (n_ace < deduct_ace) {
            deduct_ace = n_ace;
        }
        sum -= deduct_ace * 10;
    }
    return sum;
};



