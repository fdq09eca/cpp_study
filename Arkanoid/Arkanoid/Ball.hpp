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
    
    void move(int dx, int dy, Uint32 delta_time) {
        pos.x += dx;
        pos.y += dy;
    }
    
    bool collision(Brick& p, float delta_time) {
        if (p.hp <= 0)  return false;

        float b_nx = pos.x + velocity.x * delta_time;
        float b_ny = pos.y + velocity.y * delta_time;
        Point ball_next_pos(b_nx, b_ny);

        Point p_top_left    (p.pos.x            , p.pos.y);
        Point p_top_right   (p.pos.x + p.width  , p.pos.y);
        Point p_btm_left    (p.pos.x            , p.pos.y + p.height);
        Point p_btm_right   (p.pos.x + p.width  , p.pos.y + p.height);

        Line p_top          (p_top_left, p_top_right);
        Line p_left         (p_top_left, p_btm_left);
        Line p_right        (p_top_right, p_btm_right);
        Line p_btm          (p_btm_left, p_btm_right);

        Line ball_ray       (pos, ball_next_pos);
        Point intersection;

        if (ball_ray.intersection(p_top, intersection) || ball_ray.intersection(p_btm, intersection)) {
            p.hp--;
            velocity.y  = -velocity.y;
            pos         = intersection;
            return true;
        }

        if (ball_ray.intersection(p_left, intersection) || ball_ray.intersection(p_right, intersection)) {
            p.hp--;
            velocity.x  = -velocity.x;
            pos         = intersection;
            return true;
        }

        return false;
    }
    
    void collision(Paddle& p, float delta_time) {
        float b_nx = pos.x + velocity.x * delta_time;
        float b_ny = pos.y + velocity.y * delta_time;
        
        Point ball_next_pos (b_nx, b_ny);
        
        Point p_top_left    (p.pos.x            , p.pos.y           );
        Point p_top_right   (p.pos.x + p.width  , p.pos.y           );
        Point p_btm_left    (p.pos.x            , p.pos.y + p.height);
        Point p_btm_right   (p.pos.x + p.width  , p.pos.y + p.height);
        
        Line p_top      (p_top_left,    p_top_right );
        Line p_left     (p_top_left,    p_btm_left  );
        Line p_right    (p_top_right,   p_btm_right );
//        Line p_btm(p_btm_left, p_btm_right);
        
        Line ball_ray(pos, ball_next_pos);
        Point intersection;
        
        bool ball_hits_paddle = ball_ray.intersection(p_top,    intersection)
                             || ball_ray.intersection(p_left,   intersection)
                             || ball_ray.intersection(p_right,  intersection);
        
        if (ball_hits_paddle) {
            pos         = intersection;
            velocity.y  = -velocity.y;
        }
    }
    
    void update(float delta_time) {
        
        if (pos.y < 0 ) {
            velocity.y  = -velocity.y;
            pos.y       = 0;
        }
        
        if (pos.x < 0) {
            velocity.x  = -velocity.x;
            pos.x       = 0;
        }
        
        if (pos.x >= SCREEN_W) {
            velocity.x  = -velocity.x;
            pos.x       = SCREEN_W;
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
