//
//  Hand.hpp
//  blackjack
//
//  Created by ChrisLam on 17/02/2021.
//

#ifndef Hand_hpp
#define Hand_hpp

#include <stdio.h>
#include "Card.hpp"


class Hand {
    static const size_t MAX_CARD = 30;
    Card _cards[MAX_CARD];
    size_t _card_count;
public:
    Hand():_card_count(0){}
    ~Hand();
    
    void add(const Card& card);
    int point() const;
    std::ostream& print(std::ostream& s) const {
        for (size_t i = 0; i < _card_count; i++) {
            s << _cards[i] << " ";
        }
        return s;
    }
};

inline std::ostream& operator<<(std::ostream& s, const Hand& v) {
    return v.print(s);
}


#endif /* Hand_hpp */
