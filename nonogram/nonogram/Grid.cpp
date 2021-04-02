//
//  Grid.cpp
//  nonogram
//
//  Created by ChrisLam on 02/04/2021.
//

#include "Grid.hpp"
Grid::Grid(SDL_Renderer* renderer_) : renderer(renderer_) {
    size_t n = cellCount();
    for (size_t i = 0; i < n ; i++)
        cells[i]  = {255, 255, 255, 255};
};

size_t  Grid::cellCount() const { return CELL_COUNT_Y * CELL_COUNT_X; }

void Grid::draw_cell(SDL_Renderer* renderer, int x, int y, const SDL_Color& color) const {
    SDL_Color border_color = clicked_color;
    SDL_Rect rect = {x * cell_size, y * cell_size, cell_size , cell_size};

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &rect);

    SDL_SetRenderDrawColor(renderer, border_color.r, border_color.g, border_color.b, border_color.a);
    SDL_RenderDrawRect(renderer, &rect);
}


void Grid::draw() {
    for (int y = 0; y < CELL_COUNT_Y; y++) {
        for (int x = 0; x < CELL_COUNT_X; x++) {
            draw_cell(renderer, x, y, *cell(x, y));
        }
    }
}

SDL_Color* Grid::cell(int x, int y) {
    if (x < 0 || x >= CELL_COUNT_X) return nullptr;
    if (y < 0 || y >= CELL_COUNT_Y) return nullptr;
    return &cells[y * CELL_COUNT_X + x];
}

void Grid::set_cell(const Point& mousePos, const SDL_Color& color){
    int x = mousePos.x / cell_size;
    int y = mousePos.y / cell_size;

    SDL_Color* c = cell(x,y);
    if (c) {
        *c = color;
    }
}
