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
    int         score       = 0;
    int         life_count  = 3;
    bool        start       = false;
    bool        pause       = false;
    Ball        ball;
    Grid        grid;
    Paddle      paddle;
    Point       life_pos    {   g_life_offset_x, g_life_pos_y   };
    ScoreBoard  score_board {   score, 0, 0                     };

    
    Player          ();
    void init       ();
    void restart    ();
    void move       (int dx,    float delta_time);
    void collision  (float delta_time);
    void spawn_ball ();
    void die        ();
    bool won        ();
    bool lost       ();
    void draw_life  ();
    void draw_score ();
    bool update     (float delta_time);
    void render     ();
};

#endif /* Player_hpp */
