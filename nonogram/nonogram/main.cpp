//
//  main.cpp
//  nonogram
//
//  Created by ChrisLam on 24/02/2021.
//

#define SDL_MAIN_HANDLED

#include <iostream>
#include <SDL2/SDL.h>
const int SCREEN_W = 1280;
const int SCREEN_H = 720;

SDL_Color backgroundColor = {255, 255, 255, 255};

//
struct Point{
    int x;
    int y;
    Point() = default;
    Point(int x_, int y_):x(x_), y(y_){};
};

const SDL_Color clicked_color = {0, 0, 0, 255};

struct Grid {
    static const int cell_size = 20;
    SDL_Renderer* renderer = nullptr;
    static const size_t CELL_COUNT_X = SCREEN_W / cell_size;
    static const size_t CELL_COUNT_Y = SCREEN_H / cell_size;

    size_t cellCount() const { return CELL_COUNT_Y * CELL_COUNT_X; }

    SDL_Color cells[CELL_COUNT_X * CELL_COUNT_Y];
    
    Grid(SDL_Renderer* renderer_) : renderer(renderer_) {
        size_t n = cellCount();
        for (size_t i = 0; i < n ; i++) {
            cells[i]  = {255, 255, 255, 255};
        }
    };
    
    void draw_cell(SDL_Renderer* renderer, int x, int y, const SDL_Color& color) const {
        SDL_Color border_color = clicked_color;
        SDL_Rect rect = {x * cell_size, y * cell_size, cell_size , cell_size};
    
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_RenderFillRect(renderer, &rect);

        SDL_SetRenderDrawColor(renderer, border_color.r, border_color.g, border_color.b, border_color.a);
        SDL_RenderDrawRect(renderer, &rect);
    }
    
    void draw() {
        for (int y = 0; y < CELL_COUNT_Y; y++) {
            for (int x = 0; x < CELL_COUNT_X; x++) {
                draw_cell(renderer, x, y, *cell(x, y));
            }
        }
//        for (size_t i = 0; i < n; i++) {
//            cells[i].draw(renderer);
//        }
    }

    SDL_Color* cell(int x, int y) {
        if (x < 0 || x >= CELL_COUNT_X) return nullptr;
        if (y < 0 || y >= CELL_COUNT_Y) return nullptr;
        return &cells[y * CELL_COUNT_X + x];
    }

    void set_cell(const Point& mousePos, const SDL_Color& color){
        int x = mousePos.x / cell_size;
        int y = mousePos.y / cell_size;

        SDL_Color* c = cell(x,y);
        if (c) {
            *c = color;
        }
    }
};

int main(int argc, const char * argv[]) {
    
    srand(static_cast<unsigned int>(time(nullptr)));
    
    Uint32 startTime = 0;
    Uint32 endTime = 0;
    Uint32 delta = 0;
    Uint32 fps = 60;
    Uint32 timePerFrame = 16; // miliseconds
    if (SDL_Init(SDL_INIT_VIDEO) != 0) return -1;
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    
    if (SDL_CreateWindowAndRenderer(SCREEN_W, SCREEN_H, 0, &window, &renderer) != 0) return -1;
    
    SDL_bool done = SDL_FALSE;
    
    Grid grids(renderer);

    SDL_Color penColor = {0,0,0, 255};

    while (!done) {
        if (!startTime) {
            // get the time in ms passed from the moment the program started
            startTime = SDL_GetTicks();
        } else {
            delta = endTime - startTime; // how many ms for a frame
        }
        
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_KEYDOWN:
                    switch( event.key.keysym.sym ){
                        case SDLK_ESCAPE:
                            done = SDL_TRUE;
                            break;
                        case SDLK_1: penColor = SDL_Color{0, 0,   0, 255}; break;
                        case SDLK_2: penColor = SDL_Color{255, 0, 0, 255}; break;
                        case SDLK_3: penColor = SDL_Color{0, 255, 0, 255}; break;
                        case SDLK_4: penColor = SDL_Color{0, 0, 255, 255}; break;
                    }
                    printf( "Key press detected\n" );
                    break;
                
                case SDL_KEYUP:
                    printf( "Key release detected\n" );
                    break;
                    
                case SDL_QUIT:
                    done = SDL_TRUE;
                    break;
            }
        }
        
        Point mousePos;
        uint32_t mouseState = SDL_GetMouseState(&mousePos.x, &mousePos.y);

        if (mouseState & SDL_BUTTON(SDL_BUTTON_LEFT))
            grids.set_cell(mousePos, penColor);

        if (mouseState & SDL_BUTTON(SDL_BUTTON_RIGHT))
            grids.set_cell(mousePos, backgroundColor);


        grids.draw();
        SDL_RenderPresent(renderer);
        
        // if less than 16ms, delay
        if (delta < timePerFrame) {
            SDL_Delay(timePerFrame - delta);
        }
        
        // if delta is bigger than 16ms between frames, get the actual fps
        if (delta > timePerFrame) {
            fps = 1000 / delta;
        }
        
        //        printf("FPS is: %i \n", fps);
        
        startTime = endTime;
        endTime = SDL_GetTicks();
        
        
        
    }
    if (renderer) {
        SDL_DestroyRenderer(renderer);
    }
    if (window) {
        SDL_DestroyWindow(window);
    }
    SDL_Quit();
    return 0;
}
