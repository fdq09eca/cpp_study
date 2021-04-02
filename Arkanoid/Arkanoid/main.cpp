//
//  main.cpp
//  nonogram
//
//  Created by ChrisLam on 24/02/2021.
//

#define SDL_MAIN_HANDLED

#include "common.hpp"
#include "Player.hpp"


int main(int argc, const char * argv[]) {
    srand(static_cast<unsigned int>(time(NULL)));
    Uint32 startTime    = 0;
    Uint32 endTime      = 0;
    Uint32 delta        = 0;
    Uint32 fps          = 60;
    Uint32 timePerFrame = 16; // miliseconds
    if (SDL_Init(SDL_INIT_VIDEO) != 0) return -1;
    SDL_Window* window = NULL;

    if (SDL_CreateWindowAndRenderer(SCREEN_W, SCREEN_H, 0, &window, &g_renderer)) return -1;
    
    bool running = true;
    
    Uint32 last_time = SDL_GetTicks();
    Uint32 curr_time = last_time;
    float delta_time;
    
    Player player;
    
    while (running) {
        if (!startTime) {
            startTime = SDL_GetTicks();
        } else {
            delta = endTime - startTime; // how many ms for a frame
        }
        
        SDL_SetRenderDrawColor(g_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(g_renderer);
        
        last_time           = curr_time;
        curr_time           = SDL_GetTicks();
        delta_time          = (curr_time - last_time)/1000.0f;
        delta_time          = std::min(0.05f, delta_time);
        
        const int n = 100;
        for (int t = 0; t < n; t++) {
            running = player.update(delta_time / n);
            if (!running) break;
        }
        
        player.render();
        SDL_RenderPresent(g_renderer);
        
        if (delta < timePerFrame)   SDL_Delay(timePerFrame - delta);
        if (delta > timePerFrame)   fps = 1000 / delta;
        
        startTime = endTime;
        endTime = SDL_GetTicks();
        
    }
    if (g_renderer)         SDL_DestroyRenderer(g_renderer);
    if (window)             SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
};
