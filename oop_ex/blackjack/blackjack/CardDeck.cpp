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

Card CardDeck::remove(size_t idx) {
    assert(idx >= 0 && idx < _len);
    Card* dst = _cards + idx;
    Card rm_card = *dst;
    Card* src = dst + 1;
    size_t mv_element = _len - idx - 1;
    memmove(dst, src, mv_element * sizeof(Card));
    assert(_len);
    _len--;
    return rm_card;
}

Card CardDeck::draw() {
    std::srand(static_cast<unsigned int>(time(NULL)));
    if (_len == 0) {
        restart();
    }
    size_t rand_idx = std::rand() % _len;
    return remove(rand_idx);
}

const size_t& CardDeck::count_card() const{
    return _len;
}

const size_t& CardDeck::card_cap() const{
    return _cap;
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
