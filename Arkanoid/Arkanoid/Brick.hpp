//
//  Brick.hpp
//  Arkanoid
//
//  Created by ChrisLam on 22/03/2021.
//

#ifndef Brick_hpp
#define Brick_hpp

#include <stdio.h>
#include <SDL2/SDL.h>
#include "common.hpp"


struct Brick {
    Point pos{0,0};
    static const int max_hp = 4;
    int width = g_brick_width;
    int height = g_brick_height;
    int hp = 1;
    SDL_Color border_color = WHITE;
    
    Brick(){
    };
    
    void set_pos(int x, int y) {
        pos.x = x;
        pos.y = y;
    }
    
    void draw() {
        if (hp <= 0) return;
        SDL_Rect rect = {(int) pos.x, (int) pos.y, width, height};

        SDL_SetRenderDrawColor(g_renderer, 51 * (max_hp - hp), 51 * (max_hp - hp), 255, 255);
        SDL_RenderFillRect(g_renderer, &rect);

        SDL_SetRenderDrawColor(g_renderer, border_color.r, border_color.g, border_color.b, border_color.a);
        SDL_RenderDrawRect(g_renderer, &rect);
        
    }
};

#endif /* Brick_hpp */
