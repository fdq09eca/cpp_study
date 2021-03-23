//
//  Ball.hpp
//  Arkanoid
//
//  Created by ChrisLam on 23/03/2021.
//

#ifndef Ball_hpp
#define Ball_hpp

#include <stdio.h>
#include "common.hpp"

struct Ball {
    Point pos{0, 0};
    int radius = 5;
    Point velocity{-400, -50};
    SDL_Color color = RED;
    
    void set_pos(int x, int y){
        pos.x = x;
        pos.y = y;
    };
    
    void update(float delta_time) {
        
        if (pos.y < 0 ) {
            velocity.y = -velocity.y;
            pos.y = 0;
        }
        
        if (pos.x < 0) {
            velocity.x = -velocity.x;
            pos.x = 0;
        }
        
        if (pos.x >= SCREEN_W) {
            velocity.x = -velocity.x;
            pos.x = SCREEN_W;
        }
        
        
        pos.x += velocity.x * delta_time;
        pos.y += velocity.y * delta_time;
    }
    
    void draw() {
        SDL_Rect rect = {(int) pos.x - radius, (int) pos.y - radius, radius * 2, radius * 2};
        SDL_SetRenderDrawColor(g_renderer, color.r, color.g, color.b, color.a);
        SDL_RenderFillRect(g_renderer, &rect);
    }
};

#endif /* Ball_hpp */
