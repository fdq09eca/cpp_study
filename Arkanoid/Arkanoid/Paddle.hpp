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
    float width     =   SCREEN_W / 3;
    float height    =   g_brick_height / 2;
    float speed     =   1000.0f;
    Point pos       {   SCREEN_W / 2, SCREEN_H - 100    };
    SDL_Color color =   WHITE;
    
    
    void draw();
    void move(float dx, float delta_time);

};

#endif /* Paddle_hpp */
