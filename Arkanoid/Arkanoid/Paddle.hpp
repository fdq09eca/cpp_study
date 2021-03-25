//
//  Paddle.hpp
//  Arkanoid
//
//  Created by ChrisLam on 23/03/2021.
//

#ifndef Paddle_hpp
#define Paddle_hpp

#include <stdio.h>
#include "common.hpp"

struct Paddle {
    Point pos {SCREEN_W/2, SCREEN_H - 100};
    int width = SCREEN_W/3;
    int height = g_brick_height / 2;
    float speed = 1000.0f;
    SDL_Color color = WHITE;
    
    
    void draw(){
        SDL_Rect rect = {(int) pos.x, (int) pos.y, width, height};
        SDL_SetRenderDrawColor(g_renderer, color.r, color.g, color.b, color.a);
        SDL_RenderFillRect(g_renderer, &rect);
    }
    
    void move(float dx, float delta_time){
        dx *= speed * delta_time;
        pos.x = clamp( pos.x + dx, 0.0f, (float) SCREEN_W - width);
    }

};

#endif /* Paddle_hpp */
