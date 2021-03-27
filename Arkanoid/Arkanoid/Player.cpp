//
//  Player.cpp
//  Arkanoid
//
//  Created by ChrisLam on 22/03/2021.
//

#include "Player.hpp"

Player::Player()    {   spawn_ball();   }

void Player::init() {
    grid.init();        spawn_ball();
    life_count = 3;     score = 0;
    start = false;      pause = false;
}

void Player::restart(){
    init();
}

void Player::move(int dx, float delta_time) {
    paddle.move(dx, delta_time);
}

void Player::collision(float delta_time){
    ball.collision(paddle, delta_time);
    for (int r = 0; r < grid.num_row; r ++) {
        for (int c = 0; c < grid.num_col; c ++) {
            Brick& b = grid.get_brick(c, r);
            if (ball.collision(b, delta_time)) {
                score++;
            };
        }
    }
}

void Player::spawn_ball(){
    start = false;
    ball.set_pos(paddle.pos.x + paddle.width/2, paddle.pos.y - ball.radius*2);
    ball.reset_history();
}

void Player::die() {
    life_count--;
    if (lost()) return;
    spawn_ball();
}

bool Player::won() {
    for (int r = 0; r < grid.num_row; r++) {
        for (int c = 0; c < grid.num_col; c++) {
            Brick& b = grid.get_brick(c, r);
            if (b.hp > 0) return false;
        }
    }
    return true;
}

bool Player::lost() {    return life_count < 0;     }

bool Player::update(float delta_time) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_KEYDOWN:
                switch( event.key.keysym.sym ){
                    case SDLK_r:
                        restart();
                        break;
                    case SDLK_SPACE:
                        start? pause = !pause:start = true;
                        break;
                    case SDLK_ESCAPE:
                        return false;
                }
                printf( "Key press detected\n" );
                break;
            
            case SDL_KEYUP:
                printf( "Key release detected\n" );
                break;
                
            case SDL_QUIT:
                return false;
        }
    }
    
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    
    if (!pause && !lost()) {
        if (!start) spawn_ball();
        if (state[SDL_SCANCODE_LEFT]) move(-1, delta_time);
        if (state[SDL_SCANCODE_RIGHT]) move(1, delta_time);
        if (ball.pos.y > SCREEN_H) die();
        if (start) {
            collision(delta_time);
            ball.update(delta_time);
        }
        if (won()) restart();
    }
    return true;
}

void Player::draw_life() {
    for (int i = 0; i < life_count; i ++){
        int x = life_pos.x + (g_life_offset_x + g_life_width) * i;
        SDL_Rect rect = {x, (int) life_pos.y, g_life_width, g_life_height};
        SDL_Color& pc = paddle.color;
        SDL_SetRenderDrawColor(g_renderer, pc.r, pc.g, pc.b, 255);
        SDL_RenderFillRect(g_renderer, &rect);
    }
}

void Player::draw_score(){
    score_board.score = score;
    Drawer::draw(score_board);
}

void Player::render() {
    grid.draw();
    paddle.draw();
    ball.draw();
    draw_life();
    draw_score();
}
