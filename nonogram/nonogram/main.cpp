//
//  main.cpp
//  nonogram
//
//  Created by ChrisLam on 24/02/2021.
//
#include "Grid.hpp"

int main(int argc, const char * argv[]) {
    Uint32 startTime        = 0;
    Uint32 endTime          = 0;
    Uint32 delta            = 0;
    Uint32 fps              = 60;
    Uint32 timePerFrame     = 16; // miliseconds
    if (SDL_Init(SDL_INIT_VIDEO) != 0) return -1;
    SDL_Window* window      = NULL;
    SDL_Renderer* renderer  = NULL;
    
    if (SDL_CreateWindowAndRenderer(SCREEN_W, SCREEN_H, 0, &window, &renderer) != 0) return -1;
    
    SDL_bool done = SDL_FALSE;
    
    Grid grids(renderer);
    SDL_Color penColor = {0, 0, 0, 255};

    while (!done) {
        if (!startTime) {
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
                        case SDLK_ESCAPE:   done = SDL_TRUE;    break;
                        case SDLK_1:        penColor = clicked_color; break;
                        case SDLK_2:        penColor = red; break;
                        case SDLK_3:        penColor = green; break;
                        case SDLK_4:        penColor = blue; break;
                    }
                    printf( "Key press detected\n" );   break;
                case SDL_KEYUP: printf( "Key release detected\n" ); break;
                case SDL_QUIT:  done = SDL_TRUE;    break;
            }
        }
        
        Point mousePos;
        uint32_t mouseState = SDL_GetMouseState(&mousePos.x, &mousePos.y);
        if (mouseState & SDL_BUTTON(SDL_BUTTON_LEFT))   grids.set_cell(mousePos, penColor);
        if (mouseState & SDL_BUTTON(SDL_BUTTON_RIGHT))  grids.set_cell(mousePos, backgroundColor);

        grids.draw();
        SDL_RenderPresent(renderer);
        
        if (delta < timePerFrame) SDL_Delay(timePerFrame - delta);
        if (delta > timePerFrame) fps = 1000 / delta;
        startTime = endTime;
        endTime = SDL_GetTicks();
    }
    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
