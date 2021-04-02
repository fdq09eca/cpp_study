//
//  GameBoard.hpp
//  tetris
//
//  Created by ChrisLam on 02/04/2021.
//

#ifndef GameBoard_hpp
#define GameBoard_hpp

#include "Tetrimino.hpp"

struct GameBoard {
    static const int width = 10;
    static const int height = 20;
    static const int offset_x = 5;
    static const int offset_y = 5;
    
    SDL_Color background_color = WHITE;
    Cell board[width * height];

    GameBoard();
    
    Cell& get(const int x, const int y);
    void set(const int x, const int y, const int v);
    void set_piece(Tetrimino piece);
    bool is_line(int y);
    void set_line(int y, int v);
    void remove_lines_until(int dst_y);
    void draw(SDL_Renderer* renderer);
    
    
};


#endif /* GameBoard_hpp */
