//
//  common.hpp
//  nonogram
//
//  Created by ChrisLam on 02/04/2021.
//

#ifndef common_hpp
#define common_hpp

#include <stdio.h>
#include <iostream>
#include <SDL2/SDL.h>
const int SCREEN_W = 1280;
const int SCREEN_H = 720;
const SDL_Color backgroundColor = {255, 255, 255, 255};
const SDL_Color clicked_color = {0, 0, 0, 255};
const SDL_Color red = {255, 0, 0, 255};
const SDL_Color green = {0, 255, 0, 255};
const SDL_Color blue = {0, 0, 255, 255};
const int cell_size = 20;
const size_t CELL_COUNT_Y = SCREEN_H / cell_size;
const size_t CELL_COUNT_X = SCREEN_W / cell_size;
#endif /* common_hpp */
