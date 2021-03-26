//
//  Paddle.cpp
//  Arkanoid
//
//  Created by ChrisLam on 23/03/2021.
//

#include "Paddle.hpp"

void Paddle::draw(){
    SDL_Rect rect = {(int) pos.x, (int) pos.y, (int) width, (int) height};
    SDL_SetRenderDrawColor(g_renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(g_renderer, &rect);
}

void Paddle::move(float dx, float delta_time){
    dx *= speed * delta_time;
    pos.x = clamp( pos.x + dx, 0.0f, (float) SCREEN_W - width);
}
