//
//  main.cpp
//  snake
//
//  Created by ChrisLam on 23/02/2021.
//

#include <iostream>
#include <SDL2/SDL.h>
const int SCREEN_W = 1280;
const int SCREEN_H = 720;
const int SCREEN_CENTER_X = SCREEN_W/2;
const int SCREEN_CENTER_Y = SCREEN_H/2;

struct Point {
    int x;
    int y;
    Point() = default;
    Point(int x_, int y_): x(x_), y(y_){};
    
    bool operator ==(const Point& p) const {
        return p.x == x && p.y == y;
    }
};

class Snake{
    static const int MAX_TRAIL_LEN = 50;
    SDL_Renderer* _renderer = nullptr;
    int size = 20;
    Point trail[MAX_TRAIL_LEN];
    int len = 10;
    Point _position {SCREEN_CENTER_X, SCREEN_CENTER_Y};
    Point _food_position;
    Point direction {0, -1};
    bool direction_changed = false;
    bool game_over = false;
    
    
public:
    Snake(SDL_Renderer* renderer_): _renderer(renderer_){
        restart();
    }
    
    void restart(){
        game_over = false;
        direction_changed = false;
        direction.x = 0;
        direction.y = -1;
        len = 10;
        _position.x = SCREEN_CENTER_X;
        _position.y = SCREEN_CENTER_Y;
        place_food();
        for (int i = 0; i < len; i++) {
            trail[i] = _position;
        }
    }
    
    void place_food() {
        _food_position.x = rand() % (SCREEN_W / size) * size;
        _food_position.y = rand() % (SCREEN_H / size) * size;
    }
    
    bool check_gameover() {
        if (_position.x < 0 || _position.x > SCREEN_W - size) return true;
        if (_position.y < 0 || _position.y > SCREEN_H - size) return true;
        
        for (int i = 0; i < len; i++) {
            if (trail[i] == _position)
                return true;
        }
        
        return false;
    }
    
    void draw() {
        SDL_SetRenderDrawColor(_renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_Rect head {_position.x, _position.y, size, size};
        SDL_RenderFillRect(_renderer, &head);
        draw_trail();
        
        SDL_SetRenderDrawColor(_renderer, 255, 255, 0, SDL_ALPHA_OPAQUE);
        SDL_Rect food {_food_position.x, _food_position.y, size, size};
        SDL_RenderFillRect(_renderer, &food);
    }
    
    bool update() {
        direction_changed = false;
        bool extent = false;
        
        if (_position == _food_position) {
            extent = true;
            place_food();
        }
        
        if (!game_over) {
            move(direction.x, direction.y, extent);
        }
        game_over = check_gameover();
        
        draw();
        return true;
    }
    
    void draw_trail(){
        SDL_SetRenderDrawColor(_renderer, 255, 255 , 255, SDL_ALPHA_OPAQUE);
        for (int i = 0; i < len; i ++) {
            SDL_Rect rect {trail[i].x, trail[i].y, size, size};
            SDL_RenderFillRect(_renderer, &rect);
        }
    }
    
    void set_direction(int dx, int dy) {
        if (direction_changed) return;
        if (dx < 0 && direction.x > 0) return;
        if (dy < 0 && direction.y > 0) return;
        if (dx > 0 && direction.x < 0) return;
        if (dy > 0 && direction.y < 0) return;
        direction.x = dx;
        direction.y = dy;
        direction_changed = true;
    }
    
    void move(int dx, int dy, bool extent) {
        
        if (len > 0) {
            Point* dst = trail + 1;
            Point* src = trail;
            int element_to_move = std::min(len, MAX_TRAIL_LEN - 1);
            memmove(dst, src, sizeof(Point) * element_to_move);
            trail[0] = _position;
        }
        
        if (len < MAX_TRAIL_LEN && extent) {
            len++;
        }
        
        _position.x += dx * size;
        _position.y += dy * size;
        printf("\nposition x: %i, y: %i\ndirection x, y: %i, %i\n", _position.x, _position.y, direction.x, direction.y);
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
    
    Snake snake(renderer);
    
    SDL_bool done = SDL_FALSE;
    while (!done) {
        if (!startTime) {
            // get the time in ms passed from the moment the program started
            startTime = SDL_GetTicks();
        } else {
            delta = endTime - startTime; // how many ms for a frame
        }
        
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);
        
        bool running = snake.update();
        
        if (!running) {
            done = SDL_TRUE;
        }
        
        SDL_RenderPresent(renderer);
        
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_KEYDOWN:
                    switch( event.key.keysym.sym ){
                        case SDLK_LEFT:
                            snake.set_direction(-1, 0);
                            break;
                        case SDLK_RIGHT:
                            snake.set_direction(1, 0);
                            break;
                        case SDLK_UP:
                            snake.set_direction(0, -1);
                            break;
                        case SDLK_DOWN:
                            snake.set_direction(0, 1);
                            break;
                        case SDLK_ESCAPE:
                            done = SDL_TRUE;
                            break;
                        case SDLK_r:
                            snake.restart();
                            break;
                            
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
