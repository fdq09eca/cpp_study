//
//  CardDeck.hpp
//  blackjack
//
//  Created by ChrisLam on 15/02/2021.
//

#ifndef CardDeck_hpp
#define CardDeck_hpp

#include <stdio.h>
#include "Card.hpp"

class CardDeck: public Card {
private:
    Card* _cards;
    size_t _len;
    size_t _cap;

public:
    CardDeck();
    ~CardDeck();
    void clear();
    Card* remove(size_t idx);
    Card* draw();
    void restart();
    void release();
    std::ostream& print(std::ostream& s) const;
    };
        
std::ostream& operator<<(std::ostream& s , CardDeck& deck);
#endif /* CardDeck_hpp */
