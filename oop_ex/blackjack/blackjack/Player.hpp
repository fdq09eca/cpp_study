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

#include "Hand.hpp"

class Player{
    friend class Game;
    size_t _id;
    Hand _hand;
    int _money;
    int _bet;
    bool _bust;
    
public:
    Player(): _id(0), _money(100), _bust(false){}
    inline int point() const                   { return _hand.point(); }
    inline void place_bet(const int b)         { assert(b > 0 && b <= _money); _bet = b; deduct_money(b); }
    inline void add_money(const int m)         { assert(m > 0); _money += m; }
    inline void deduct_money(const int m)      { assert(m > 0); _money -= m; }
    inline bool bust()                         { _bust = point() > 21; return _bust; }
    std::ostream& print(std::ostream& s) const;
    
};

inline std::ostream& operator<< (std::ostream& s , const Player& p) {
    return p.print(s);
}
#endif /* Player_hpp */
