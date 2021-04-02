//
//  Cell.cpp
//  tetris
//
//  Created by ChrisLam on 02/04/2021.
//

#include "Cell.hpp"


Cell::Cell() = default;


void Cell::set_pos(int x_, int y_) {
    pos.x = x_;
    pos.y = y_;
}

void Cell::set_color(SDL_Color color_) {
    color = color_;
}


void Cell::draw(SDL_Renderer* renderer, int offset_x, int offset_y) {
    SDL_Rect rect = { (pos.x + offset_x) * size,
                      (pos.y + offset_y) * size,
                       size, size
                    };

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &rect);

    SDL_SetRenderDrawColor(renderer, border_color.r, border_color.g, border_color.b, border_color.a);
    SDL_RenderDrawRect(renderer, &rect);
}
