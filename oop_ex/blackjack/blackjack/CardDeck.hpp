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
#include "Player.hpp"
#include "Dealer.hpp"

class CardDeck: public Card {
private:
    CardDeck(const CardDeck& d);
    void operator=(const CardDeck& d);
    Card* _cards;
    size_t _remain;
    size_t _n_cards;
    size_t _n_deck;
    

public:
    CardDeck(const size_t n_deck = 1);
    ~CardDeck();
    void clear();
    void release();
    
    inline size_t remain() const { return _remain; }
    inline size_t n_cards() const { return _n_cards; }
    
    
    

//    CardDeck& remove(const Card& card);
    Card draw();
    void draw_to(Player& p);
    void draw_to(Dealer& d);
    
    void restart();
    void restart(size_t n_deck);
    void shuffle(size_t t_time = 1);
    
//    const size_t& count() const;
//    const size_t& cap() const;
    std::ostream& print(std::ostream& s) const;
};
        
inline std::ostream& operator<<(std::ostream& s , CardDeck& deck) { return deck.print(s); }

//TEST
void TEST_CardDeck();

#endif /* CardDeck_hpp */
 
