//
//  Game.hpp
//  blackjack
//
//  Created by ChrisLam on 17/02/2021.
//

#ifndef Game_hpp
#define Game_hpp

#include <stdio.h>

#include "Player.hpp"
#include "Dealer.hpp"
#include "CardDeck.hpp"

class Game {
    Dealer _dealer;
    
    const static size_t MAX_PLAYERS = 7;
    Player _players[MAX_PLAYERS];
    size_t _n_players;
    size_t _n_stand_players;
    size_t _n_bust_players;
    
    CardDeck _deck;
    size_t _n_deck;
    

public:    
    Game(): _n_players(0), _n_deck(1), _n_stand_players(0), _n_bust_players(0) {}
    void init();
    void set_n_player();
    void set_n_deck();
    
    void player_place_bet(Player& player);
    void players_place_bet();
    void player_hit_or_stand(Player& player);
    void players_hit_or_stand();
    void player_lose(Player& player);
    void dealer_bust();
    void dealer_lose(Player& player);
    void check_winner(Player& player);
    void deal_to_player(Player& player, size_t n_card);
    void deal_to_players(size_t n_card);
    void deal_to_dealer(size_t n_card);
    
    void dealer_hit_or_stand();
    void remove(Player& player);
    
    inline bool players_side_end()                    { return _n_players == 0 || _n_players == _n_stand_players; }
    inline bool dealer_side_end()                     { return _dealer._money <= 0 || _dealer.point() > 21; }
    
    void account();
    
    void run();
    std::ostream& print(std::ostream& s) const;
    
};


inline std::ostream& operator<< (std::ostream& s , const Game& g) {
    return g.print(s);
}

#endif /* Game_hpp */

