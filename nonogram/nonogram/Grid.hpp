//
//  Grid.hpp
//  nonogram
//
//  Created by ChrisLam on 02/04/2021.
//

#ifndef Grid_hpp
#define Grid_hpp
#include "Point.hpp"
#include "common.hpp"

struct Grid {
    SDL_Renderer* renderer = nullptr;
    SDL_Color cells[CELL_COUNT_X * CELL_COUNT_Y];
    size_t cellCount() const;
    
    Grid(SDL_Renderer* renderer_);
    SDL_Color* cell(int x, int y);
    void draw();
    void draw_cell(SDL_Renderer* renderer, int x, int y, const SDL_Color& color) const;
    void set_cell(const Point& mousePos, const SDL_Color& color);
};


#endif /* Grid_hpp */
