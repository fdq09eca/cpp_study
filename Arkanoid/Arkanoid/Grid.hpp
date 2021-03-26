//
//  Grid.hpp
//  Arkanoid
//
//  Created by ChrisLam on 22/03/2021.
//

#ifndef Grid_hpp
#define Grid_hpp

#include <stdio.h>
#include "Brick.hpp"

struct Grid {
    static const int num_row = 8;
    static const int num_col = 12;
    const int brick_count = num_row * num_col;
    Point pos{0,0};
    Brick data[num_row][num_col];
    
    Grid(){
        init();
    }
    
    void init(){
        for (int r = 0; r < num_row ; r++) {
            for (int c = 0; c < num_col; c++) {
                Brick& b = get_brick(c, r);
                b.set_pos((int) c * g_brick_width + g_offset_x, (int) r * g_brick_height + g_offset_y);
                
                b.hp = (num_row - r) % b.max_hp;
                if (!b.hp) b.hp = 1;
            }
        }
    }

    
    Brick& get_brick(int col, int row) {
        assert(row >= 0 && row < num_row );
        assert(col >= 0 && col < num_col );
        return data[row][col];
    }
    
    void draw() {
        for (int r = 0; r < num_row ; r++) {
            for (int c = 0; c < num_col; c++) {
                Brick& b = get_brick(c, r);
                b.draw();
            }
        }
    }
};

#endif /* Grid_hpp */
