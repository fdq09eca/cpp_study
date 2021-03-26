//
//  Ball.cpp
//  Arkanoid
//
//  Created by ChrisLam on 23/03/2021.
//

#include "Ball.hpp"

void Ball::set_pos(int x, int y){
    pos.x = x;
    pos.y = y;
};

void Ball::init(){
    velocity.x = 800;
    velocity.y = -300;
}

void Ball::move(int dx, int dy, Uint32 delta_time) {
    pos.x += dx;
    pos.y += dy;
}

bool Ball::collision(Brick& p, float delta_time) {
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

void Ball::collision(Paddle& p, float delta_time) {
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
    Line p_btm(p_btm_left, p_btm_right);
    
    Line ball_ray(pos, ball_next_pos);
    Point intersection;
    
    bool ball_hits_paddle   =   ball_ray.intersection(p_top,     intersection)
                            ||  ball_ray.intersection(p_left,    intersection)
                            ||  ball_ray.intersection(p_right,   intersection)
                            ||  ball_ray.intersection(p_btm,     intersection);
    
    if (ball_hits_paddle) {
        pos         = intersection;
        velocity.y  = -velocity.y;
    }
    
}

void Ball::update(float delta_time) {
    
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

void Ball::reset_history(){
    for (int i = 0; i < history_count; i++) {
        history[i].x = pos.x;
        history[i].y = pos.y;
    }
}

void Ball::draw() {
    
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
