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
    static const int num_row = 7;
    static const int num_col = 16;
    Point pos{0,0};
    Brick data[num_row][num_col];
    
    Grid(){
        for (int r = 0; r < num_row ; r++) {
            for (int c = 0; c < num_col; c++) {
                Brick& b = get_brick(c, r);
                b.set_pos(c * g_brick_width, r * g_brick_height);
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
