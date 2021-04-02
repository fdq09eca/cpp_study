//
//  Player.hpp
//  tetris
//
//  Created by ChrisLam on 02/04/2021.
//

#ifndef Player_hpp
#define Player_hpp
#include "GameBoard.hpp"
#include "Tetriminos.hpp"

struct Player {
    SDL_Renderer*   renderer = nullptr;
    GameBoard       board;
    Tetrimino       curr_piece;
    Tetrimino       next_piece;
    Tetriminos      pieces;
    Uint32          spwan_time;
    Uint32          cum_time;
    Uint32          time_out = 100;
    
    Player(SDL_Renderer* renderer_);
    
    bool is_overlapped(int px, int py, const Tetrimino& piece);
    void clean_line();
    void move(int dx, int dy);
    void rotate();
    void hard_drop();
    void counter_rotate();
    void spawn_curr_piece();
    void render();
    bool update(Uint32 delta_time);
    
};

#endif /* Player_hpp */
