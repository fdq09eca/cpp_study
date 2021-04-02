//
//  Cell.hpp
//  tetris
//
//  Created by ChrisLam on 02/04/2021.
//

#ifndef Cell_hpp
#define Cell_hpp

#include "Point.hpp"
#include "common.hpp"

struct Cell {
    static const int    size = 20;
    int                 value = 0;
    Point               pos;
    SDL_Color           color;
    SDL_Color           border_color = BLACK;

    Cell();
    void set_pos(int x_, int y_);
    void set_color(SDL_Color color_);
    void draw(SDL_Renderer* renderer, int offset_x = 5, int offset_y = 5);
};
#endif /* Cell_hpp */
