//
//  common.cpp
//  Arkanoid
//
//  Created by ChrisLam on 22/03/2021.
//

#include "common.hpp"

SDL_Renderer* g_renderer = nullptr;

Point::Point(float x_, float y_):x(x_), y(y_){};

float Point::distance(const Point& p) const {
    float dx = x - p.x;
    float dy = y - p.y;
    return sqrt(dx * dx + dy * dy);
}

bool Point::is_between(const Point& p1, const Point& p2) const {
    return fabs(p1.distance(p2) - distance(p1) - distance(p2)) < FLT_EPSILON;
}

Line::Line(const Point& p1_, const Point& p2_): p1(p1_), p2(p2_) {
    float dy = p2.y - p1.y;
    float dx = p2.x - p1.x;
    slope = dy / dx;
    c =  - slope * p1.x + p1.y;
}

bool Line::intersection(const Line& l, Point& interscetion) const{
    float x1 =   p1.x;      float y1 =   p1.y;
    float x2 =   p2.x;      float y2 =   p2.y;
    
    float x3 = l.p1.x;      float y3 = l.p1.y;
    float x4 = l.p2.x;      float y4 = l.p2.y;
    
    float denom     = (y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1);
    float numer_a   = (x4 - x3) * (y1 - y3) - (y4 - y3) * (x1 - x3);
    float numer_b   = (x2 - x1) * (y1 - y3) - (y2 - y1) * (x1 - x3);
    
    bool parallel = float_eq(denom, 0.0f);
    bool coincident = float_eq(numer_a, 0.0f) && float_eq(numer_b, 0.0f) && float_eq(denom, 0.0f);
    
    if (parallel) return false;
    
    if (coincident) {
        interscetion.x = (x1 + x2) / 2;
        interscetion.y = (y1 + y2) / 2;
        return true;
    }
    
    float u_a = numer_a / denom;
    float u_b = numer_b / denom;
    
    bool out_of_range = u_a < 0 || u_a > 1 || u_b < 0  || u_b > 1;
    
    if (out_of_range) return false;
    
    interscetion.x = x1 + u_a * (x2 - x1);
    interscetion.y = y1 + u_a * (y2 - y1);
    
    return true;
};

void Numbers::draw(int n, Point pos, int cell_size, SDL_Color color) {
    assert( n>= 0 && n < N);
    for (int y = 0; y < H ; y++) {
        for (int x = 0; x < W ; x++) {
            const int& i = data[n][y][x];
            if (!i) continue;
            SDL_Rect rect = {(int) pos.x + x * cell_size, (int) pos.y + y * cell_size, cell_size, cell_size};
            SDL_SetRenderDrawColor(g_renderer, color.r, color.g, color.b, color.a);
            SDL_RenderFillRect(g_renderer, &rect);
            SDL_RenderDrawRect(g_renderer, &rect);
        }
    }
}

ScoreBoard::ScoreBoard(int score_, int x, int y):pos(x, y), score(score_){
    for (int i = 0; i < board_size; i++) {
        board[i] = 0;
    }
}

void ScoreBoard::set_board_max() {
    for (int i = 0 ; i < board_size;i++) {
        board[i] = 9;
    }
}

void ScoreBoard::write() {
    int s = score;
    for (int i = 0; i < board_size; i++) {
        board[i] = s % 10;
        s /= 10;
    }
}

int ScoreBoard::max_score() {
    return pow(10, board_size) - 1;
}

void Drawer::draw(ScoreBoard& sb) {
    sb.score >= sb.max_score()? sb.set_board_max() : sb.write();
    Point p = sb.pos;
    for (int i = 0; i < sb.board_size; i++) {
        int n = sb.board[sb.board_size - i - 1];
        sb.num.draw(n, p);
        p.x += sb.num.next_num_x;
    }
}

void Drawer::draw(const Point& p, int size) {
    SDL_Rect rect = {(int) p.x, (int) p.y, size, size};
    SDL_SetRenderDrawColor(g_renderer, 255/2, 255/2, 0, 255);
    SDL_RenderFillRect(g_renderer, &rect);
}

void Drawer::draw(const Line& l) {
        SDL_SetRenderDrawColor(g_renderer, 255, 0, 0, 255);
        SDL_RenderDrawLine(g_renderer, (int) l.p1.x, (int) l.p1.y, (int) l.p2.x, (int) l.p2.y);
}
