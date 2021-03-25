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
    static const int history_count = 100;
    int radius = 5;
    Point pos{0, 0};
    Point velocity{800, -300};
    Point history[history_count];
    SDL_Color color = RED;
    
    
    int history_idx = 0;
    
    void set_pos(int x, int y){
        pos.x = x;
        pos.y = y;
    };
    
    void init(){
        velocity.x = 800;
        velocity.y = -300;
    }
    
    void move(int dx, int dy) {
        pos.x += dx;
        pos.y += dy;
    }
    
    bool collision(Brick& b) {
        if (b.hp <= 0) return false;
        
        float bx0 = b.pos.x;
        float bx1 = b.pos.x + b.width;
        float by0 = b.pos.y;
        float by1 = b.pos.y + b.height;

        if (!(pos.x >= bx0 && pos.x <= bx1 && pos.y >= by0 && pos.y <= by1)) return false;
        
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
            return true;
        }

        if (velocity.x < 0 && velocity.y > 0) {
            if (dy0 < dx1) {
                pos.y = by0;
                velocity.y = -velocity.y;
            } else {
                pos.x = bx1;
                velocity.x = -velocity.x;
            }
            return true;
        }

        if (velocity.x > 0 && velocity.y > 0) {
            if (dy0 < dx0) {
                pos.y = by0;
                velocity.y = -velocity.y;
            } else {
                pos.x = bx0;
                velocity.x = -velocity.x;
            }
            return true;
        }

        if (velocity.x > 0 && velocity.y < 0) {
            if (dy1 < dx0) {
                pos.y = by1;
                velocity.y = -velocity.y;
            } else {
                pos.x = bx0;
                velocity.x = -velocity.x;
            }
            return true;
        }
        return false;
    }
    
    void collision(Paddle& p, float delta_time) {

        float dx = velocity.x * delta_time;
        float dy = velocity.y * delta_time;
        Point ball_next_pos(pos.x + dx, pos.y + dy);
        Line ball_ray(pos, ball_next_pos);
        
        ball_ray.draw();
        
        for (int i = 0; i < 100; i++) {
            ball_ray.given_x(ball_ray.p1.x + i).draw();
        }
        
        Point p_top_left(p.pos.x , p.pos.y);
        Point p_top_right(p.pos.x + p.width , p.pos.y);
        Point p_bottom_left(p.pos.x , p.pos.y + p.height);
        Point p_bottom_right(p.pos.x + p.width , p.pos.y + p.height);
        
        Line p_top(p_top_left, p_top_right);
        Line p_left(p_top_left, p_bottom_left);
        Line p_right(p_top_right, p_bottom_right);
        Line p_bottom(p_bottom_left, p_bottom_right);
        
        if (ball_ray.interscetion(p_top).is_between(pos, ball_next_pos)) {
            Point i = ball_ray.interscetion(p_top);
            i.draw(50);
            std::cout << "ball_ray.interscetion(p_top): " <<i.x<<","<<i.y<<"\n";
            pos = ball_ray.interscetion(p_top);
            velocity.y = - velocity.y;
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
    
    void reset_history(){
        for (int i = 0; i < history_count; i++) {
            history[i].x = pos.x;
            history[i].y = pos.y;
        }
    }
    
    void draw() {
        
        for (int i = 0; i < history_count; i++){
            Point& hist = history[i];
            SDL_Rect rect = {(int) hist.x - radius, (int) hist.y - radius, radius * 2, radius * 2};
            SDL_SetRenderDrawColor(g_renderer, 0, 255/2, 255/2, 255);
            SDL_RenderFillRect(g_renderer, &rect);
        }
        
        SDL_Rect rect = {(int) pos.x - radius, (int) pos.y - radius, radius * 2, radius * 2};
        SDL_SetRenderDrawColor(g_renderer, color.r, color.g, color.b, color.a);
        SDL_RenderFillRect(g_renderer, &rect);
        
        
    }
};

#endif /* Ball_hpp */
