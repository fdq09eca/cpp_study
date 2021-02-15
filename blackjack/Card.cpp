#include "Card.hpp"
#include "iostream"

void next_suit(Suit &s){
    switch (s) {
        case Suit_DIAMOND:
            s = Suit_CLUB;
            return;
        case Suit_CLUB:
            s = Suit_HEART;
            return;
        case Suit_HEART:
            s =  Suit_SPADE;
            return;
        case Suit_SPADE:
            s =  Suit_DIAMOND;
            return;
        default:
            s = Suit_NONE;
            return;
    }
}

const int Card::parse_rank(const char r) const {
    switch (r) {
        case 'A': return 1;
        case 'J': return 11;
        case 'Q': return 12;
        case 'K': return 13;
        default:
            int v = r - '0';
            assert(v > 1 && v < 13);
            return v;
    }
}

const char* Card::rank_str() const {
    static const char* rank_name[] = {"N/A", "A", "2", "3", "4", "5", "6", "7" ,"8", "9" ,"10", "J", "Q", "K"};
    assert(_rank >= 1 && _rank <= 13);
    return rank_name[_rank];
}

const char* Card::suit_str() const {
    static const char* suit_name[] = {"D", "C", "H", "S"};
    assert(_suit >= 0 && _suit<= 3);
    return suit_name[_suit];
}

const Suit Card::suit() const{
    return _suit;
}

const int Card::rank() const{
    return _rank;
}

const int Card::value() const{
    return _value;
}

const int Card::set_value(int rank){
    if (rank == 1){
        return 'A';
    }
    if (rank > 10) {
        return 10;
    };
    return rank;
}

std::ostream& operator << (std::ostream& s, Card& card){
    s << card.suit_str() << "-" << card.rank_str() << " value: " << card.value();
    return s;
}
