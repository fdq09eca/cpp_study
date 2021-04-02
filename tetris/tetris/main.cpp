//
//  main.cpp
//  nonogram
//
//  Created by ChrisLam on 24/02/2021.
//

#define SDL_MAIN_HANDLED
#include "Player.hpp"
    
int main(int argc, const char * argv[]) {
    srand(static_cast<unsigned int>(time(NULL)));
    std::cout << rand() <<"\n";
    Uint32 startTime = 0;
    Uint32 endTime = 0;
    Uint32 delta = 0;
    Uint32 fps = 60;
    Uint32 timePerFrame = 16; // miliseconds
    if (SDL_Init(SDL_INIT_VIDEO) != 0) return -1;
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    
    if (SDL_CreateWindowAndRenderer(SCREEN_W, SCREEN_H, 0, &window, &renderer) != 0) return -1;
    
    Player player(renderer);
    
    SDL_bool done = SDL_FALSE;
    Uint32 last_time = SDL_GetTicks();
    Uint32 curr_time = last_time;
    Uint32 delta_time;
    while (!done) {
        if (!startTime) {
            // get the time in ms passed from the moment the program started
            startTime = SDL_GetTicks();
        } else {
            delta = endTime - startTime; // how many ms for a frame
        }
        
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);
        last_time   = curr_time;
        curr_time   = SDL_GetTicks();
        delta_time  = curr_time - last_time;
        
        if (!player.update(delta_time)) break;
        player.render();

        SDL_RenderPresent(renderer);
    
        if (delta < timePerFrame) SDL_Delay(timePerFrame - delta);
        if (delta > timePerFrame) fps = 1000 / delta;
        startTime   = endTime;
        endTime     = SDL_GetTicks();
        
    }
    if (renderer)   SDL_DestroyRenderer(renderer);
    if (window)     SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
