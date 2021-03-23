//
//  Player.hpp
//  Arkanoid
//
//  Created by ChrisLam on 22/03/2021.
//

#ifndef Player_hpp
#define Player_hpp

#include <stdio.h>
#include "Grid.hpp"
#include "Paddle.hpp"
#include "Ball.hpp"

struct Player {
    Grid grid;
    Paddle paddle;
    Ball ball;
    
    Player(){
        ball.set_pos(paddle.pos.x + paddle.width/2, paddle.pos.y - ball.radius*2);
    }
    
    void move(int dx, float delta_time) {
        paddle.move(dx, delta_time);
    }
    
    bool update(float delta_time) {
        SDL_Event event;
        ball.update(delta_time);
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_KEYDOWN:
                    switch( event.key.keysym.sym ){
                        case SDLK_LEFT:
                            move(-1, delta_time);
                            break;
                        case SDLK_RIGHT:
                            move(1, delta_time);
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
        return true;
        
    }
    
    void render() {
        grid.draw();
        paddle.draw();
        ball.draw();
        
    }
};

#endif /* Player_hpp */
