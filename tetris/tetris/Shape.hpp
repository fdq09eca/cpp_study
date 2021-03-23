//
//  Shape.hpp
//  tetris
//
//  Created by ChrisLam on 20/03/2021.
//

#ifndef Shape_hpp
#define Shape_hpp

#include <stdio.h>

#endif /* Shape_hpp */

struct Shape {
    static const int width = 4;
    static const int height = 4;
    int data[width][height];
    
    Shape(){};
    
    Shape(int* data_) {
        init(data_);
    };
    
    void init(int* data_) {
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width;x++) {
                data[x][y] = data_[y * width + x];
            }
        }
    }
};
