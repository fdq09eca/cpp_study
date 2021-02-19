//
//  CardDeck.cpp
//  blackjack
//
//  Created by ChrisLam on 15/02/2021.
//

#include "Player.hpp"
#include "CardDeck.hpp"
#include "common.h"


CardDeck::CardDeck(size_t n_deck_): _remain(0), _n_deck(n_deck_){
    _n_cards = 52 * _n_deck;
    _cards = new Card[_n_cards];
    if (!_cards) {
        throw std::runtime_error("failed to new _cards");
    }
    restart();
}


CardDeck::~CardDeck(){
    release();
}

void CardDeck::release() {
    clear();
    delete [] _cards;
    _cards = nullptr;
}

void CardDeck::clear() {
    _remain = 0;
}

void CardDeck::restart() {
    if (!_cards) return;
    clear();
    Card* card = _cards;
    for (int n = 0; n < _n_deck; n++){
        for (Rank r = Rank_ACE; r <= Rank_K ; rank_inc(r)) {
            for (Suit s = Suit_DIAMOND;s <= Suit_SPADE; card++, suit_inc(s)) {
                *card = Card(s, r);
            }
        }
    }
    _remain = _n_cards;
}



void CardDeck::restart(size_t n_deck) {
    release();
    _n_deck = n_deck;
    _n_cards = _n_deck * 52;
    _cards = new Card[_n_cards];
    restart();
}

Card CardDeck::draw() {
    assert(_remain > 0);
    Card card = _cards[_remain - 1];
    _remain--;
    return card;
}

void CardDeck::shuffle(size_t t_times) {
    for (size_t t = 0; t < t_times; t++){
        for (size_t i = 0; i < _remain; i++) {
            int j = std::rand() % _remain;
            if (i == j) continue;
            std::swap(_cards[i], _cards[j]);
        }
    }
}

void CardDeck::draw_to(Player& p){
    p.add_card(draw());
}

void CardDeck::draw_to(Dealer& d){
    d.add_card(draw());
}

std::ostream& CardDeck::print(std::ostream& s) const{
    Card* card = _cards;
    Card* end = _cards + _remain;
    for (size_t c = 0; card < end ; card++, c++) {
        s << "Card" << c << ": " << *card << "\n";
    };
    return s;
}


/// TEST

void TEST_CardDeck(){
    CardDeck d(1);
    d.shuffle();
    dump_var(d);
    dump_var(d.draw());
    TEST(d.remain() == 51);
    
}
