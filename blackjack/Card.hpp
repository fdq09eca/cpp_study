#ifndef Card_hpp
#define Card_hpp

#include <stdio.h>
#include <iostream>

enum Suit{
    Suit_DIAMOND,
    Suit_CLUB,
    Suit_HEART,
    Suit_SPADE,
    Suit_NONE = -1,
};

void next_suit(Suit &s);

class Card{
    
private:
    Suit _suit;
    int _rank;
    int _value;
    static const int set_value(int rank);
    
    

public:
    Card():_suit(Suit_NONE), _rank(0), _value(0){};
    Card(const Suit s, const int r): _suit(s), _rank(r), _value(set_value(r)){};
    Card(const Suit s, const char r): _suit(s){
        Card(s, parse_rank(r));
    };
   
    const int parse_rank (const char r) const;
    const char* rank_str() const;
    const char* suit_str() const;
    const Suit suit() const;
    const int rank() const;
    const int value() const;
    
    
};


std::ostream& operator << (std::ostream& s, Card& card);

#endif
