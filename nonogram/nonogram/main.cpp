//
//  main.cpp
//  nonogram
//
//  Created by ChrisLam on 24/02/2021.
//

#include <iostream>
#include <SDL2/SDL.h>
const int SCREEN_W = 1280;
const int SCREEN_H = 720;
//
struct Point{
    int x;
    int y;
    Point(){};
    Point(int x_, int y_):x(x_), y(y_){};
};
//
struct Grid {
    static const int size = 20;
    Point pos;
    SDL_Renderer* renderer = NULL;
    SDL_Color clicked_color = {0, 0, 0, 255};
    SDL_Color original_color = {255, 255, 255, 255};
    SDL_Rect body = {pos.x, pos.y, size , size};
    bool clicked = false;
    
    Grid(){};
    Grid(SDL_Renderer* renderer_, int x, int y): renderer(renderer_), pos(x, y){};
    
    void draw() const {
        SDL_Color c = color();
        SDL_Color border_color = clicked_color;
        SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
        SDL_RenderFillRect(renderer, &body);
        SDL_SetRenderDrawColor(renderer, border_color.r, border_color.g, border_color.b, border_color.a);
        SDL_RenderDrawRect(renderer, &body);
    }
    
    SDL_Color color() const {
        return clicked? clicked_color : original_color;
    }
    
    bool in_range(Point p) const {
        return p.x >= pos.x && p.x <= pos.x + size && p.y >= pos.y && p.y <= pos.y + size;
    }
    
    void reset() {
        clicked = false;
    }
    
};

struct Grids {
    SDL_Renderer* renderer = nullptr;
    static const size_t X = SCREEN_W/Grid::size;
    static const size_t Y = SCREEN_H/Grid::size;
    Grid grids[X*Y];
    int mx, my;
    
    Grids(SDL_Renderer* renderer){
        int i = 0;
        for (int x = 0; x < SCREEN_W; x += Grid::size){
            for (int y = 0; y < SCREEN_H; y += Grid::size){
                grids[i] = Grid(renderer, x, y);
                i++;
            }
        }
    };
    
    void draw() {
        size_t n = X * Y;
        for (size_t i = 0; i < n; i++) {
            grids[i].draw();
        }
    }
    
    void reset(){
        size_t n = X * Y;
        for (size_t i = 0; i < n; i++) {
            grids[i].reset();
        }
    }
    
    void update(){
        size_t n = X * Y;
        Point mouse_point(mx, my);
        for (size_t i = 0; i < n; i++) {
            Grid& grid = grids[i];
            if (grid.in_range(mouse_point)) {
                grid.clicked = !grid.clicked;
            }
        }
    }
};

int main(int argc, const char * argv[]) {
    
    srand(static_cast<unsigned int>(time(nullptr)));
    
    Uint32 startTime = 0;
    Uint32 endTime = 0;
    Uint32 delta = 0;
    short fps = 60;
    short timePerFrame = 150; // miliseconds
    if (SDL_Init(SDL_INIT_VIDEO) != 0) return -1;
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    
    if (SDL_CreateWindowAndRenderer(SCREEN_W, SCREEN_H, 0, &window, &renderer) != 0) return -1;
    
    SDL_bool done = SDL_FALSE;
    
    Grids grids(renderer);

    while (!done) {
        if (!startTime) {
            // get the time in ms passed from the moment the program started
            startTime = SDL_GetTicks();
        } else {
            delta = endTime - startTime; // how many ms for a frame
        }
        
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);
        SDL_GetMouseState(&grids.mx, &grids.my);
        SDL_Event event;
        grids.draw();
        SDL_RenderPresent(renderer);
        
        
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_KEYDOWN:
                    switch( event.key.keysym.sym ){
                        case SDLK_ESCAPE:
                            done = SDL_TRUE;
                            break;
                        case SDLK_r:
                            grids.reset();
                            break;
                    }
                    printf( "Key press detected\n" );
                    break;
                
                case SDL_MOUSEBUTTONDOWN:
                    switch (event.button.button) {
                        case SDL_BUTTON_LEFT:
                            grids.update();
                            break;
                        case SDL_BUTTON_RIGHT:
                            grids.reset();
                            break;
                        default:
                            break;
                    }
                    
                case SDL_KEYUP:
                    printf( "Key release detected\n" );
                    break;
                    
                case SDL_QUIT:
                    done = SDL_TRUE;
                    break;
            }
        }
        
        
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
