//
//  Game.cpp
//  blackjack
//
//  Created by ChrisLam on 17/02/2021.
//

#include "Game.hpp"


std::ostream& Game::print(std::ostream& s) const {
    s << "\n==================\n"
    << _dealer << "\n";
    for (size_t i = 0; i < _n_players; i ++) {
        s << _players[i] << "\n";
    }
    s << "#CARD REMAIN: " << _deck.remain() << "\n"
    << "#PLAYER REMAIN: " << _n_players << "\n"
    << "\n==================\n";
    return s;
}

void Game::init() {
    set_n_player();
    set_n_deck();
    std::cout << "== GAME START ==\n";
    _deck.shuffle();
    players_place_bet();
    deal_to_dealer(2);
    deal_to_players(2);
    std::cout << *this;
    
    while (!players_side_end()) {
        players_hit_or_stand();
    }
    
    if (!_n_players) {
        std::cout    <<"\n== ALL PLAYERS BUST. DEALER WINS ==\n";
        std::cout << *this;
        std::cout << "== GAME OVER ==\n";
        return;
    }
    
    dealer_hit_or_stand();
    if (_dealer.bust()) {
        dealer_bust();
        std::cout << "\n== DEALER BUSTED. PLAYERS WINS ==\n";
        std::cout << *this;
        std::cout << "\n== GAME OVER ==\n";
        return;
    }
    
    account();
    std::cout << *this;
    std::cout << "\n== GAME OVER ==\n";
}

void Game::account(){
    for (int i = 0; i < _n_players; i++) {
        check_winner(_players[i]);
    }
}

void Game::check_winner(Player& player) {
    if (player.point() > _dealer.point()) {
        dealer_lose(player);
        return;
    }
    if (player.point() < _dealer.point()) {
        player_lose(player);
        return;
    }
    std::cout << "\n== PLAYER" << player._id << "[DRAW]: $" << player._bet <<"\n" << player << "\n";
    player.add_money(player._bet);
}

void Game::dealer_hit_or_stand(){
    while (true) {
        char ans = 0;
        std::cout << _dealer << "\n[H]it or [S]tand?\n<< ";
        std::cin >> ans;
        
        if (!strchr("HhSs", ans)){
            std::cout << "\n== [H] for Hit, [S] for Stand ==\n";
            continue;
        }
        
        if (strchr("Ss", ans)) {
            std::cout << "== DEALER STAND ==\n";
            return;
        }
        
        deal_to_dealer(1);
        if (_dealer.bust())
            return;
    }
}

void Game::player_place_bet(Player& player) {
    int bet = 0;
    while (!bet) {
        std::cout << "<< PLAYER" << player._id << " >> $" << player._money << "\n"
        << "Total bet: $" << player._bet << "\n"
        << "Place bet: \n>> ";
        
        std::cin >> bet;
        
        if (bet > player._money) {
            std::cout << "== Not enough money. ==\n";
            continue;
        }
        
        if (bet > 0) break;
        std::cout << "== Bet must be > 0. ==\n";
    }
    player.place_bet(bet);
}



void Game::players_place_bet() {
    for (int i = 0; i < _n_players; i++) {
        player_place_bet(_players[i]);
    }
}

void Game::player_hit_or_stand(Player& player) {
    char ans = 0;
    while (true) {
        
        std::cout << player << "\nHit or Stand? [H/S]\n<< ";
        std::cin >> ans;
        if (!strchr("HhSs", ans)){
            std::cout << "[H] for Hit, [S] for Stand\n";
            continue;
        }
        
        if (strchr("Ss", ans)) {
            _n_stand_players++;
            std::cout << "\n== PLAYER" << player._id << " STAND. ==\n";
            return;
        }
        
        deal_to_player(player, 1);
        
        if (player.bust()) {
            std::cout << "\n== PLAYER" << player._id << " BUST ==\n";
            player_lose(player);
            remove(player); // bug here.
            return;
        }
    }
}

void Game::dealer_bust() {
    for (int i = 0; i < _n_players; i++) {
        Player& player = _players[i];
        dealer_lose(player);
    }
}

void Game::dealer_lose(Player &player){
    std::cout << "\n== PLAYER" << player._id << " [WON]: $" << player._bet <<"\n" << player;
    player.add_money(player._bet * 2);
    _dealer.deduct_money(player._bet);
}

void Game::player_lose(Player &player) {
    std::cout << "\n== PLAYER" << player._id << " [LOSE]: $" << player._bet <<"==\n" << player << "\n";
    _dealer.add_money(player._bet);
    player._bet = 0;
    return;
}

void Game::players_hit_or_stand(){
    for (int i = 0; i < _n_players; i++) {
        Player& player = _players[i];
        player_hit_or_stand(player);
    }
}


void Game::set_n_player() {
    while (!_n_players) {
        std::cout << "How many players? Max " << MAX_PLAYERS << "\n>> ";
        std::cin >> _n_players;
        if (_n_players > MAX_PLAYERS) {
            _n_players = 0;
        }
    }
    for (int i = 0; i < _n_players; i++) {
        _players[i]._id = i + 1;
    }
}

void Game::set_n_deck() {
    std::cout << "How many deck? \n>> ";
    std::cin >> _n_deck;
    _deck.restart(_n_deck);
}

void Game::deal_to_dealer(size_t n_cards) {
    for (size_t n = 0; n < n_cards; n++) {
        _dealer._hand.add(_deck.draw());
    }
}

void Game::deal_to_player(Player &player, size_t n_cards){
    for (size_t n = 0; n < n_cards; n++) {
        player._hand.add(_deck.draw());
    }
}

void Game::deal_to_players(size_t n_cards) {
    for (size_t i = 0; i < _n_players; i++) {
        deal_to_player(_players[i], n_cards);
    }
}

void Game::remove(Player& player) {
    Player* d = &player;
    Player* s = &player + 1;
    Player* e = _players + _n_players;
    for ( ;s < e; d++, s++) {
        *d = *s;
    }
    _n_players--;
}

void Game::run(){
    init();
}
