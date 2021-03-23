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
#include "Brick.hpp"
#include "Paddle.hpp"

struct Ball {    
    Point pos{0, 0};
    int radius = 5;
    Point velocity{800, -100};
    SDL_Color color = RED;
    static const int history_count = 100;
    Point history[history_count];
    int history_idx = 0;
    
    void set_pos(int x, int y){
        pos.x = x;
        pos.y = y;
    };
    
    void collision(Brick& b) {
        if (b.hp <= 0) return;
        
        float bx0 = b.pos.x;
        float bx1 = b.pos.x + b.width;
        float by0 = b.pos.y;
        float by1 = b.pos.y + b.height;

        if (!(pos.x >= bx0 && pos.x <= bx1 && pos.y >= by0 && pos.y <= by1)) return;
        
        b.hp--;

        float dy0 = abs(pos.y - by0);
        float dy1 = abs(pos.y - by1);
        float dx0 = abs(pos.x - bx0);
        float dx1 = abs(pos.x - bx1);
        
        if (velocity.x < 0 && velocity.y < 0) {
            if (dy1 < dx1) {
                pos.y = by1;
                velocity.y = -velocity.y;
            } else {
                pos.x = bx1;
                velocity.x = -velocity.x;
            }
            return;
        }

        if (velocity.x < 0 && velocity.y > 0) {
            if (dy0 < dx1) {
                pos.y = by0;
                velocity.y = -velocity.y;
            } else {
                pos.x = bx1;
                velocity.x = -velocity.x;
            }
            return;
        }

        if (velocity.x > 0 && velocity.y > 0) {
            if (dy0 < dx0) {
                pos.y = by0;
                velocity.y = -velocity.y;
            } else {
                pos.x = bx0;
                velocity.x = -velocity.x;
            }
            return;
        }

        if (velocity.x > 0 && velocity.y < 0) {
            if (dy1 < dx0) {
                pos.y = by1;
                velocity.y = -velocity.y;
            } else {
                pos.x = bx0;
                velocity.x = -velocity.x;
            }
            return;
        }
                
    }
    
    void collision(Paddle& b) {
        
        float bx0 = b.pos.x;
        float bx1 = b.pos.x + b.width;
        float by0 = b.pos.y;
        float by1 = b.pos.y + b.height;

        if (!(pos.x >= bx0 && pos.x <= bx1 && pos.y >= by0 && pos.y <= by1)) return;
        
        float dy0 = abs(pos.y - by0);
        float dy1 = abs(pos.y - by1);
        float dx0 = abs(pos.x - bx0);
        float dx1 = abs(pos.x - bx1);
        
        if (velocity.x < 0 && velocity.y < 0) {
            if (dy1 < dx1) {
                pos.y = by1;
                velocity.y = -velocity.y;
            } else {
                pos.x = bx1;
                velocity.x = -velocity.x;
            }
            return;
        }

        if (velocity.x < 0 && velocity.y > 0) {
            if (dy0 < dx1) {
                pos.y = by0;
                velocity.y = -velocity.y;
            } else {
                pos.x = bx1;
                velocity.x = -velocity.x;
            }
            return;
        }

        if (velocity.x > 0 && velocity.y > 0) {
            if (dy0 < dx0) {
                pos.y = by0;
                velocity.y = -velocity.y;
            } else {
                pos.x = bx0;
                velocity.x = -velocity.x;
            }
            return;
        }

        if (velocity.x > 0 && velocity.y < 0) {
            if (dy1 < dx0) {
                pos.y = by1;
                velocity.y = -velocity.y;
            } else {
                pos.x = bx0;
                velocity.x = -velocity.x;
            }
            return;
        }
    }
    
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
        
        
        history[history_idx %= history_count] = pos;
        history_idx++;
        
        pos.x += velocity.x * delta_time;
        pos.y += velocity.y * delta_time;
        
    }
    
    void draw() {
        SDL_Rect rect = {(int) pos.x - radius, (int) pos.y - radius, radius * 2, radius * 2};
        SDL_SetRenderDrawColor(g_renderer, color.r, color.g, color.b, color.a);
        SDL_RenderFillRect(g_renderer, &rect);
        
        for (int i = 0; i < history_count; i++){
            
            SDL_Rect rect = {(int) history[i].x - radius, (int) history[i].y - radius, radius * 2, radius * 2};
            SDL_SetRenderDrawColor(g_renderer, 0, 255/2, 255/2, 255);
            SDL_RenderFillRect(g_renderer, &rect);
            
        }
    }
};

#endif /* Ball_hpp */
