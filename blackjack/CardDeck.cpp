//
//  CardDeck.cpp
//  blackjack
//
//  Created by ChrisLam on 15/02/2021.
//

#include "CardDeck.hpp"

CardDeck::CardDeck(): _len(0), _cap(52){
    _cards = new Card[_cap];
    restart();
}

CardDeck::~CardDeck(){
    delete [] _cards;
    _cards = nullptr;
    _len = 0;
    _cap = 0;
}

void CardDeck::clear() {
    _len = 0;
}

void CardDeck::restart() {
    if (!_cards) return;
    Card* card = _cards;
    Card* end = _cards + _cap;
    for (int r = 1; card < end ; r++) {
        for (Suit s = Suit_DIAMOND;s <= Suit_SPADE; card++, _len++) {
            *card = Card(s, r);
            s = static_cast<Suit>(static_cast<int>(s) + 1);
        }
    };
}

std::ostream& CardDeck::print(std::ostream& s) const{
    Card* card = _cards;
    Card* end = _cards + _cap;
    for (size_t c = 0; card < end ; card++, c++) {
        s << "Card" << c << ": " << *card << "\n";
    };
    return s;
}

std::ostream& operator<<(std::ostream& s , CardDeck& deck) {
    return deck.print(s);
};
