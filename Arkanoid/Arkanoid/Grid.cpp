//
//  Grid.cpp
//  Arkanoid
//
//  Created by ChrisLam on 22/03/2021.
//

#include "Grid.hpp"


Grid::Grid(){   init(); }

void Grid::init(){
    for (int r = 0; r < num_row ; r++) {
        for (int c = 0; c < num_col; c++) {
            Brick& b = get_brick(c, r);
            b.set_pos((int) c * g_brick_width + g_offset_x, (int) r * g_brick_height + g_offset_y);
            b.hp = (num_row - r) % b.max_hp;
            if (!b.hp) b.hp = 1;
        }
    }
}

Brick& Grid::get_brick(int col, int row) {
    assert(row >= 0 && row < num_row );
    assert(col >= 0 && col < num_col );
    return data[row][col];
}

void Grid::draw() {
    for (int r = 0; r < num_row ; r++) {
        for (int c = 0; c < num_col; c++) {
            Brick& b = get_brick(c, r);
            b.draw();
        }
    }
}
