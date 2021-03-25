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

const int SCREEN_W = 800;
const int SCREEN_H = 1024;
const SDL_Color WHITE = {255, 255, 255, 255};
const SDL_Color BLACK = {0, 0, 0, 255};
const SDL_Color RED = {255, 0, 0, 255};
const SDL_Color BLUE = {0, 0, 255, 255};
const int g_brick_width = SCREEN_W/15;
const int g_brick_height = 20;
const int g_offset_x = 100;
const int g_offset_y = 100;

const int g_life_width = SCREEN_W/20;
const int g_life_height = 5;
const int g_life_offset_x = 20;
const int g_life_offset_y = 20;
const int g_life_pos_y = SCREEN_H - g_life_offset_y;

extern SDL_Renderer* g_renderer;

struct Point {
    
    float x = 0.0f;
    float y = 0.0f;
    
    Point() = default;
    inline Point(float x_, float y_):x(x_), y(y_){};
};

struct Line {
    Point p1;
    Point p2;
    float slope = 1;
    float c = 0;
    
    Line(Point p1_, Point p2_): p1(p1_), p2(p2_) {
        float dy = p2.y - p1.y;
        float dx = p2.x - p1.x;
        slope = dy / dx;
        c = slope * p1.x + p1.y;
    }
    
    Point given_x(float x) {
        assert(slope);
        float y = slope * x + c;
        return Point(x, y);
    }
    
    Point given_y(float y) {
        assert(slope);
        float x = (y - c) / slope;
        return Point(x, y);
    }
    
    bool has_point(Point p) {
        return p.y == given_x(p.x).y;
    }
    
    bool is_intersect(Line l) {
        return l.slope != slope;
    }
    
    Point interscetion(Line l) {
        assert(is_intersect(l));
        float x = (c - l.c) / (l.slope - slope);
        return given_x(x);
    };
};

struct Life {
    Point pos;
    int width = SCREEN_W/10;
    int height = 20;
    SDL_Color color = WHITE;
    
    void set_pos(int x, int y) {
        pos.x = x; pos.y = y;
    }
};


struct Numbers{
    static const int N = 10;
    static const int W = 3;
    static const int H = 5;
    static const int cell_size = 10;
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
    
    void draw(int n, Point pos, int cell_size = 10, SDL_Color color = WHITE) {
        assert( n>= 0 && n < N);
        for (int y = 0; y < H ; y++) {
            for (int x = 0; x < W ; x++) {
                const int& i = data[n][y][x];
                if (!i) continue;
                SDL_Rect rect = {(int) pos.x + x * cell_size, (int) pos.y + y * cell_size, cell_size, cell_size};
                SDL_SetRenderDrawColor(g_renderer, color.r, color.g, color.b, color.a);
                SDL_RenderFillRect(g_renderer, &rect);
//                SDL_SetRenderDrawColor(g_renderer, BLACK.r, BLACK.g, BLACK.b, BLACK.a);
                SDL_RenderDrawRect(g_renderer, &rect);
            }
        }
    }
};

struct ScoreBoard {
    
    static const int board_size = 5;
    int score;
    Point pos;
    Numbers num;
    int board[board_size];
    
    
    ScoreBoard(int score_, int x = 0, int y = 0):pos(x, y), score(score_){
        for (int i = 0; i < board_size; i++) {
            board[i] = 0;
        }
    }
    
    void set_board_max() {
        for (int i = 0 ; i < board_size;i++) {
            board[i] = 9;
        }
    }
    
    void write() {
        int s = score;
        for (int i = 0; i < board_size; i++) {
            board[i] = s % 10;
            s /= 10;
        }
    }
    
    int max_score() {
        return pow(10, board_size) - 1;
    }
    
    void draw() {
        score >= max_score()? set_board_max() : write();
        
        Point p = pos;
        for (int i = 0; i < board_size; i++) {
            int n = board[board_size - i - 1];
            num.draw(n, p);
            p.x += num.next_num_x;
        }
    }
};

inline int clamp(int value, int min, int max) {
    return value < min? min : (value > max? max: value);
}




#endif /* common_hpp */
