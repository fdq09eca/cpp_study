//
//  Dealer.cpp
//  blackjack
//
//  Created by ChrisLam on 17/02/2021.
//

#include "Dealer.hpp"
#include "Player.hpp"

void Dealer::add_money(const int m){
    if (m < 0) return;
    _money += m;
}

void Dealer::deduct_money(const int m){
    if (m < 0) return;
    _money -= m;
}

bool Dealer::bust(){
    _bust = point() > 21;
    return _bust;
}



std::ostream& Dealer::print(std::ostream& s) const {
    s << "[ DEALER ]"<< "[$" << _money << "]" << "[" << _hand.point() <<"pt]\t" << _hand;
    return s;
}
