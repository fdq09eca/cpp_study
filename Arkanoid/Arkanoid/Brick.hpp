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
    int width = g_brick_width;
    int height = g_brick_height;
//    bool is_hit = false;
    int hp = 1;
    SDL_Color color = BLUE;
    SDL_Color border_color = WHITE;
    
    Brick(){};
    
    void set_pos(int x, int y) {
        pos.x = x;
        pos.y = y;
    }
    
    void draw() {
        if (hp <= 0) return;
        SDL_Rect rect = {(int) pos.x, (int) pos.y, width, height};

        SDL_SetRenderDrawColor(g_renderer, color.r, color.g, color.b, color.a);
        SDL_RenderFillRect(g_renderer, &rect);

        SDL_SetRenderDrawColor(g_renderer, border_color.r, border_color.g, border_color.b, border_color.a);
        SDL_RenderDrawRect(g_renderer, &rect);
        
    }
};

#endif /* Brick_hpp */
