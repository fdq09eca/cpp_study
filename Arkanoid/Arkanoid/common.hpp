//
//  common.hpp
//  Arkanoid
//
//  Created by ChrisLam on 22/03/2021.
//

#ifndef common_hpp
#define common_hpp

#include <stdio.h>
#include <iostream>
#include <SDL2/SDL.h>


struct Point {
    
    float x = 0.0f;
    float y = 0.0f;
    
    Point() = default;
    inline Point(float x_, float y_):x(x_), y(y_){};
};

inline int clamp(int value, int min, int max) {
    return value < min? min : (value > max? max: value);
}

const int SCREEN_W = 800;
const int SCREEN_H = 1024;
const SDL_Color WHITE = {255, 255, 255, 255};
const SDL_Color BLACK = {0, 0, 0, 255};
const SDL_Color RED = {255, 0, 0, 255};
const SDL_Color BLUE = {0, 0, 255, 255};
const int g_brick_width = SCREEN_W/20;
const int g_brick_height = 15;
const int g_offset_x = 100;
const int g_offset_y = 100;

extern SDL_Renderer* g_renderer;

#endif /* common_hpp */
