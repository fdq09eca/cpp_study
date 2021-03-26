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
    static const int    max_hp  = 4;
    int                 hp      = 1;
    float               width   = g_brick_width;
    float               height  = g_brick_height;
    Point pos   {   0,  0   };
    SDL_Color border_color = WHITE;
    
    
    
    Brick() = default;
    void set_pos(int x, int y);
    void draw();
};

#endif /* Brick_hpp */
