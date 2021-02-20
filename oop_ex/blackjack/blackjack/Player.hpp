//
//  Player.hpp
//  blackjack
//
//  Created by ChrisLam on 17/02/2021.
//

#ifndef Player_hpp
#define Player_hpp

#include <stdio.h>
#include <string.h>

//#include "Dealer.hpp"
#include "Hand.hpp"

class Dealer;

class Player{
    friend class Game;
    size_t _id;
    Hand _hand;
    int _money;
    int _bet;
    bool _bust;
    
public:
    Player(): _id(0), _money(100), _bet(0), _bust(false) {}
    inline void add_card(const Card& card)               { _hand.add(card); }
    inline int point() const                             { return _hand.point(); }
    void place_bet(const int b);
    void add_money(const int m);
    void deduct_money(const int m);
    bool bust();
    void lose(Dealer& d);
    void win(Dealer& d);
    std::ostream& print(std::ostream& s) const;
    
};

inline std::ostream& operator<< (std::ostream& s , const Player& p) {
    return p.print(s);
}
#endif /* Player_hpp */
