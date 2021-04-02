//
//  Tetriminos.hpp
//  tetris
//
//  Created by ChrisLam on 02/04/2021.
//

#ifndef Tetriminos_hpp
#define Tetriminos_hpp

#include "Tetrimino.hpp"

struct Tetriminos {
    static const int count = 7;
    int shapes[count][Tetrimino::width * Tetrimino::height] = {
        { // T
            0, 1, 0, 0,
            1, 1, 1, 0,
            0, 0, 0, 0,
            0, 0, 0, 0,
        },
        { // O
            1, 1, 0, 0,
            1, 1, 0, 0,
            0, 0, 0, 0,
            0, 0, 0, 0,
        },
        { // I
            0, 1, 0, 0,
            0, 1, 0, 0,
            0, 1, 0, 0,
            0, 1, 0, 0,
        },
        { // L
            0, 1, 0, 0,
            0, 1, 0, 0,
            0, 1, 1, 0,
            0, 0, 0, 0,
        },
        { // J
            0, 1, 0, 0,
            0, 1, 0, 0,
            1, 1, 0, 0,
            0, 0, 0, 0,
        },
        { // S
            0, 1, 1, 0,
            1, 1, 0, 0,
            0, 0, 0, 0,
            0, 0, 0, 0,
        },
        { // Z
            1, 1, 0, 0,
            0, 1, 1, 0,
            0, 0, 0, 0,
            0, 0, 0, 0,
        },
        
    };
    
    Tetrimino tetriminos[count]; // [t1, t2, t3, t4, t5, t6]
    
    Tetriminos() {
        for (int i = 0; i < count ; i++) {
            tetriminos[i].init(shapes[i], 0, 0);
        }
    }
    
    Tetrimino get(int i, int x_ = 0, int y_ = 0) {
        assert(i >= 0 && i < count);
        Tetrimino piece = tetriminos[i];
        piece.pos.x = x_;
        piece.pos.y = y_;
        return piece;
    }
    
    Tetrimino rand_get(int x_ = 0, int y_ = 0) {
        int i = rand() % count;
        return get(i, x_, y_);
    }
    
};

#endif /* Tetriminos_hpp */
