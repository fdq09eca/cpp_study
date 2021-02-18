#include "Card.hpp"
#include "iostream"
#include "common.h"

const char* Card::rank_str() const {
    static const char* rank_name[] = {"N/A", "A", "2", "3", "4", "5", "6", "7" ,"8", "9" ,"10", "J", "Q", "K"};
    assert(_rank > Rank_NONE && _rank < Rank_LAST);
    return rank_name[_rank];
}

const char* Card::suit_str() const {
    static const char* suit_name[] = {"N/A", "D", "C", "H", "S"};
    assert(_suit > Suit_NONE && _suit< Suit_LAST);
    return suit_name[_suit];
}



std::ostream& operator << (std::ostream& s, const Card& card){
    s << card.suit_str() << "[" << card.rank_str() << "]";
    return s;
}

///
void TEST_Card(){
    Card DA(Suit_DIAMOND, Rank_ACE);
    Card SA(Suit_SPADE, Rank_ACE);
    Card HK(Suit_HEART, Rank_K);
    Card CJ(Suit_CLUB, Rank_J);
    
    //    Card CA(Suit_DIAMOND, 'A');
    Card D3(Suit_DIAMOND, Rank_3);
    Card D4(Suit_DIAMOND, Rank_4);
    dump_var(SA);
    dump_var(HK);
    dump_var(CJ);
    dump_var(D3);
    TEST(D3 < D4);
    TEST(DA < SA);
    TEST(DA < D3);
}
