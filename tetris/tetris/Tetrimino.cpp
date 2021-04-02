//
//  Tertrimino.cpp
//  tetris
//
//  Created by ChrisLam on 02/04/2021.
//

#include "Tetrimino.hpp"

Tetrimino::Tetrimino() = default;

void Tetrimino::init(int* data_, int x_, int y_){
    pos.x = x_;
    pos.y = y_;
    for (int x = 0; x < width; x++) { // x is col
        for (int y = 0; y < height; y++) { // y is row
            int i       = y * width + x; //
            Cell& cell  = data[i];
            int v       = data_[i];
            cell.value  = v;
            cell.set_pos(pos.x + x, pos.y + y);
            if (!cell.value) continue;
            cell.color  = RED;
        }
    }
}

void Tetrimino::move(int x, int y) {
    pos.x += x;
    pos.y += y;
}

void Tetrimino::set_data(int* data_) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int i = y * width + x;
            data[i].value = data_[i];
        }
    }
}

void Tetrimino::counter_rotate() {
    int new_data[width*height];
    
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int dst_y = height - x - 1;
            int dst_x = y;
            new_data[dst_y * width + dst_x] = get_cell(x, y).value;
        }
    }
    set_data(new_data);
}

void Tetrimino::rotate() {
    int new_data[width*height];
    
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int dst_y = x;
            int dst_x = height - y - 1;
            new_data[dst_y * width + dst_x] = get_cell(x, y).value;
        }
    }
    set_data(new_data);
}

Cell& Tetrimino::get_cell(int x, int y){
    return data[y * width + x];
}

void Tetrimino::draw(SDL_Renderer* renderer) {
    for (int x = 0; x < width; x++) { // x is col
        for (int y = 0; y < height; y++) { // y is row
            Cell& cell = get_cell(x, y);
            cell.set_pos(pos.x + x, pos.y + y);
            if (!cell.value) continue;
            cell.color = RED;
            cell.draw(renderer);
        }
    }
}
