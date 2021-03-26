//
//  Brick.cpp
//  Arkanoid
//
//  Created by ChrisLam on 22/03/2021.
//

#include "Brick.hpp"

void Brick::set_pos(int x, int y) {
    pos.x = x;
    pos.y = y;
}

void Brick::draw() {
    if (hp <= 0) return;
    SDL_Rect rect = {(int) pos.x, (int) pos.y, (int)width, (int)height};

    SDL_SetRenderDrawColor(g_renderer, 51 * (max_hp - hp), 51 * (max_hp - hp), 255, 255);
    SDL_RenderFillRect(g_renderer, &rect);

    SDL_SetRenderDrawColor(g_renderer, border_color.r, border_color.g, border_color.b, border_color.a);
    SDL_RenderDrawRect(g_renderer, &rect);
    
}
