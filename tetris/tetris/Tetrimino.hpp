//
//  Tertrimino.hpp
//  tetris
//
//  Created by ChrisLam on 02/04/2021.
//

#ifndef Tertrimino_hpp
#define Tertrimino_hpp

#include "Cell.hpp"
struct Tetrimino {
    static const int width  = 4;
    static const int height = 4;
    Point   pos;
    Cell    data[width * height];
    
    Tetrimino();
    
    Cell&   get_cell(int x, int y);
    void    init(int* data_, int x_, int y_);
    void    move(int x, int y);
    void    set_data(int* data_);
    void    counter_rotate();
    void    rotate();
    void    draw(SDL_Renderer* renderer);
};

#endif /* Tertrimino_hpp */
