//
//  common.hpp
//  Arkanoid
//
//  Created by ChrisLam on 22/03/2021.
//

#ifndef common_hpp
#define common_hpp

#include <stdio.h>
#include <iostream>
#include <SDL2/SDL.h>


const int SCREEN_W          = 800;
const int SCREEN_H          = 1024;
const int g_life_width      = SCREEN_W / 20;
const int g_life_height     = 5;
const int g_life_offset_x   = 20;
const int g_life_offset_y   = 20;
const int g_life_pos_y      = SCREEN_H - g_life_offset_y;

const float g_brick_width   = SCREEN_W / 15;
const float g_brick_height  = 20;
const float g_offset_x      = 100.0f;
const float g_offset_y      = 100.0f;


const   SDL_Color       WHITE       = { 255 , 255   , 255   , 255  };
const   SDL_Color       BLACK       = { 0   , 0     , 0     , 255  };
const   SDL_Color       RED         = { 255 , 0     , 0     , 255  };
const   SDL_Color       BLUE        = { 0   , 0     , 255   , 255  };

extern  SDL_Renderer*   g_renderer;

inline int      clamp       (int value, int min, int max)           { return value < min? min : (value > max? max: value); }
inline float    clamp       (float value, float min, float max)     { return value < min? min : (value > max? max: value); }
inline bool     float_eq    (float a, float b)                      { return fabs(a - b) < FLT_EPSILON; }

struct Point {
    float x = 0.0f;     float y = 0.0f;
    Point() = default;
    
    Point(float x_, float y_);
    float   distance    (const Point& p) const;
    bool    is_between  (const Point& p1, const Point& p2) const;
};

struct Line {
    Point p1;           Point p2;
    float slope = 1;
    float c = 0;
    Line                (const Point& p1_,const Point& p2_);
    bool intersection   (const Line& l, Point& interscetion) const;
};

struct Numbers{
    static const int N          = 10;
    static const int W          = 3;
    static const int H          = 5;
    static const int cell_size  = 10;
    static const int next_num_x = W * cell_size + 5;
    
    int data[N][H][W] = {
        {
            {1, 1, 1},
            {1, 0, 1},
            {1, 0, 1},
            {1, 0, 1},
            {1, 1, 1},
        },
        {
            {0, 1, 0},
            {1, 1, 0},
            {0, 1, 0},
            {0, 1, 0},
            {1, 1, 1},
        },
        {
            {1, 1, 1},
            {0, 0, 1},
            {1, 1, 1},
            {1, 0, 0},
            {1, 1, 1},
        },
        {
            {1, 1, 1},
            {0, 0, 1},
            {1, 1, 1},
            {0, 0, 1},
            {1, 1, 1},
        },
        {
            {1, 0, 1},
            {1, 0, 1},
            {1, 1, 1},
            {0, 0, 1},
            {0, 0, 1},
        },
        {
            {1, 1, 1},
            {1, 0, 0},
            {1, 1, 1},
            {0, 0, 1},
            {1, 1, 1},
        },
        {
            {1, 1, 1},
            {1, 0, 0},
            {1, 1, 1},
            {1, 0, 1},
            {1, 1, 1},
        },
        {
            {1, 1, 1},
            {0, 0, 1},
            {0, 0, 1},
            {0, 0, 1},
            {0, 0, 1},
        },
        {
            {1, 1, 1},
            {1, 0, 1},
            {1, 1, 1},
            {1, 0, 1},
            {1, 1, 1},
        },
        {
            {1, 1, 1},
            {1, 0, 1},
            {1, 1, 1},
            {0, 0, 1},
            {1, 1, 1},
        },
    };
    
    void draw(int n, Point pos, int cell_size = 10, SDL_Color color = WHITE);
};

struct ScoreBoard {
    
    int                 score;
    static const int    board_size = 5;
    int                 board[board_size];
    Point               pos;
    Numbers             num;
    
    ScoreBoard(int score_, int x = 0, int y = 0);
    
    void    set_board_max();
    void    write();
    int     max_score();
};

struct Drawer {
    static void draw(       ScoreBoard& sb              );
    static void draw(const  Line&       l               );
    static void draw(const  Point&      p, int size = 10);
};

#endif /* common_hpp */
