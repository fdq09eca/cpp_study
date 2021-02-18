//
//  Player.cpp
//  blackjack
//
//  Created by ChrisLam on 17/02/2021.
//

#include "Player.hpp"


std::ostream& Player::print(std::ostream& s) const {
    s << "[ PLAYER" << _id << " ][$"<< _money << "][" << _hand.point() <<"pt]\t" << _hand;
    return s;
}
