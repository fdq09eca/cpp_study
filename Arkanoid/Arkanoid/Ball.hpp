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
    static const int history_count  = 100;
    int             radius          = 5;
    int             history_idx     = 0;
    SDL_Color       color           = RED;
    Point           pos       {   0  , 0     };
    Point           velocity  {   800, -300  };
    Point           history[history_count];
    
    
    
    void set_pos(int x, int y);
    void init();
    void move(int dx, int dy, Uint32 delta_time);
    bool collision(Brick& p, float delta_time);
    void collision(Paddle& p, float delta_time);
    void update(float delta_time);
    void reset_history();
    void draw();
};

#endif /* Ball_hpp */
