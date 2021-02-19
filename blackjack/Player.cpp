//
//  Player.cpp
//  blackjack
//
//  Created by ChrisLam on 17/02/2021.
//

#include "Player.hpp"
#include "Dealer.hpp"

void Player::add_money(const int m){
    if (m < 0) return;
    _money += m;
}

void Player::deduct_money(const int m){
    if (m < 0) return;
    _money -= m;
}

bool Player::bust(){
    _bust = point() > 21;
    return _bust;
}

void Player::lose(Dealer& d){
    d.add_money(_bet);
    _bet = 0;
}

void Player::win(Dealer& d){
    d.deduct_money(_bet);
    add_money(_bet);
    _bet = 0;
}

void Player::place_bet(const int b){
    _bet = b;
    deduct_money(b);
}

std::ostream& Player::print(std::ostream& s) const {
    s << "[ PLAYER" << _id << " ][$"<< _money << "][" << _hand.point() <<"pt]\t" << _hand;
    return s;
}
