//
//  Player.cpp
//  tetris
//
//  Created by ChrisLam on 02/04/2021.
//

#include "Player.hpp"

Player::Player(SDL_Renderer* renderer_):renderer(renderer_){
    next_piece = pieces.rand_get(board.width + 2);
    spawn_curr_piece();
}

bool Player::is_overlapped(int px, int py, const Tetrimino& piece) {
    Tetrimino tmp = piece;
    tmp.pos.x = px;
    tmp.pos.y = py;
    for (int y = 0; y < tmp.height; y++) {
         for (int x = 0; x < tmp.width; x++) {
             int i = y * tmp.width + x;
             Cell& cell = tmp.data[i];
             if (cell.value) {
                 cell.set_pos(px + x, py + y);
                 if (cell.pos.x >= GameBoard::width)     return true;
                 if (cell.pos.x < 0)                     return true;
                 if (cell.pos.y >= GameBoard::height)    return true;
                 if (cell.pos.y < 0)                     return true;
                 if (board.get(px + x, py + y).value)    return true;
             }
         }
     }
     return false;
 }

void Player::clean_line() {
    for (int y = 0; y < curr_piece.height; y++) {
        for (int x = 0; x < curr_piece.width; x++) {
            Cell& p_cell = curr_piece.get_cell(x, y);
            if (!p_cell.value)      continue;
            int py = p_cell.pos.y;
            if (board.is_line(py))  board.remove_lines_until(py);
        }
    }
}

void Player::move(int dx, int dy) {
    int nx = dx + curr_piece.pos.x;
    int ny = dy + curr_piece.pos.y;
    
    if (is_overlapped(nx, ny, curr_piece)) {
        if (dy > 0) {
            board.set_piece(curr_piece);
            clean_line();
            spawn_curr_piece();
        }
        return;
    }
    curr_piece.move(dx, dy);
}

void Player::rotate(){
    Tetrimino tmp = curr_piece;
    tmp.rotate();
    if (is_overlapped(tmp.pos.x, tmp.pos.y, tmp)) return;
    curr_piece.rotate();
}

void Player::hard_drop(){
    while (!is_overlapped(curr_piece.pos.x, curr_piece.pos.y + 1, curr_piece))  move(0, 1);
    curr_piece.draw(renderer);
    move(0, 1);
}

void Player::counter_rotate(){
    Tetrimino tmp = curr_piece;
    tmp.counter_rotate();
    if (is_overlapped(tmp.pos.x, tmp.pos.y, tmp)) return;
    curr_piece.counter_rotate();
}

void Player::spawn_curr_piece(){
    curr_piece          = next_piece;
    curr_piece.pos.x    = 0;
    curr_piece.pos.y    = 0;
    spwan_time          = SDL_GetTicks();
    next_piece          = pieces.rand_get(board.width + 2);
}

void Player::render() {
    board.draw(renderer);
    curr_piece.draw(renderer);
    next_piece.draw(renderer);
}

bool Player::update(Uint32 delta_time){
    cum_time += delta_time;
    if (cum_time > time_out) {
        move(0, 1);
        cum_time = 0;
    }
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_KEYDOWN:
                switch( event.key.keysym.sym ){
                    case SDLK_LEFT:     move(-1, 0);            break;
                    case SDLK_RIGHT:    move(1, 0);             break;
                    case SDLK_DOWN:     move(0, 1);             break;
                    case SDLK_UP:       move(0, -1);            break;
                    case SDLK_r:        rotate();               break;
                    case SDLK_1:        spawn_curr_piece();     break;
                    case SDLK_q:        counter_rotate();       break;
                    case SDLK_SPACE:    hard_drop();            break;
                    case SDLK_ESCAPE:   return false;
                }           printf( "Key press detected\n"   ); break;
            case SDL_KEYUP: printf( "Key release detected\n" ); break;
            case SDL_QUIT:  return false;
        }
    }
    return true;
}
