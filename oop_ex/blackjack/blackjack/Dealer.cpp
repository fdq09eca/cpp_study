//
//  Dealer.cpp
//  blackjack
//
//  Created by ChrisLam on 17/02/2021.
//

#include "Dealer.hpp"


std::ostream& Dealer::print(std::ostream& s) const {
    s << "[ DEALER ]"<< "[$" << _money << "]" << "[" << _hand.point() <<"pt]\t" << _hand;
    return s;
}
