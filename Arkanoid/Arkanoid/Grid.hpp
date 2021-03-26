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
    static const int brick_count = num_row * num_col;
    Point pos{0,0};
    Brick data[num_row][num_col];
    
    Grid();
    
    void    init();
    Brick&  get_brick(int col, int row);
    void    draw();
};

#endif /* Grid_hpp */
