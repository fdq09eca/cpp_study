//
//  Dealer.hpp
//  blackjack
//
//  Created by ChrisLam on 17/02/2021.
//

#ifndef Dealer_hpp
#define Dealer_hpp

#include <stdio.h>
#include <string.h>

#include "Hand.hpp"

class Player;

class Dealer{
    friend class Game;
    Hand _hand;
    int _money;
    bool _bust;

public:
    Dealer(): _money(1000), _bust(false) {}
    inline int point() const                   { return _hand.point(); }
    inline void add_card(const Card& card)     { _hand.add(card); }
    void add_money(const int m);
    void deduct_money(const int m);
    bool bust();
    void lose(Player& p);
    void win(Player& p);
    std::ostream& print(std::ostream& s) const;
    
};

inline std::ostream& operator<<(std::ostream& s, const Dealer& v) {
    return v.print(s);
}

#endif /* Dealer_hpp */


