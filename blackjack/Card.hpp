#ifndef Card_hpp
#define Card_hpp

#include <stdio.h>
#include <iostream>

enum Suit{
    Suit_NONE,
    Suit_DIAMOND,
    Suit_CLUB,
    Suit_HEART,
    Suit_SPADE,
    Suit_LAST
};

enum Rank{
    Rank_NONE,
    Rank_ACE, Rank_2,
    Rank_3, Rank_4, Rank_5,
    Rank_6, Rank_7, Rank_8,
    Rank_9, Rank_10, Rank_J,
    Rank_Q, Rank_K,
    Rank_LAST
};

inline int rank_to_int(Rank r)  { return static_cast<int>(r); }
inline int suit_to_int(Suit s)  { return static_cast<int>(s); }
inline void rank_inc(Rank& r)   { r = static_cast<Rank>(rank_to_int(r) + 1); }
inline void suit_inc(Suit& s)   { s = static_cast<Suit>(suit_to_int(s) + 1); }

class Card{
    
private:
    Suit _suit;
    Rank _rank;
public:
    Card(Suit s = Suit_NONE, Rank r = Rank_NONE):_suit(s), _rank(r){}
    const char* rank_str() const;
    const char* suit_str() const;
    inline Suit suit() const                        { return _suit; }
    inline Rank rank() const                        { return _rank; }
    inline int rank_int() const                     { return rank_to_int(_rank); }
    inline bool operator==(const Card& card) const  { return _rank  == card._rank && _suit  == card._suit; }
    inline bool operator<(const Card& card) const   { return _rank == card._rank? _suit < card._suit : _rank < card._rank; }
    
};


std::ostream& operator << (std::ostream& s, const Card& card);
void TEST_Card();
#endif
