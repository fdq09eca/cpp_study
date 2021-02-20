/*This source code copyrighted by Lazy Foo' Productions (2004-2020)
 and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include <SDL2/SDL.h>
#include <iostream>

const int SCREEN_W = 640;
const int SCREEN_H = 480;

void draw_line(SDL_Renderer* renderer, int x1, int y1, int x2, int y2){
    
    if (x1 == x2 && y1 == y2) {
        SDL_RenderDrawPoint(renderer, x1, y1);
        return;
    }
    
    if (x1 == x2) {
        for (; y1 != y2;) {
            y1 < y2? y1++ : y1--;
            SDL_RenderDrawPoint(renderer, x1, y1);
        }
        return;
    }
    
    if (y1 == y2) {
        for (; x1 != x2; ){
            x1 < x2? x1++ : x1--;
            SDL_RenderDrawPoint(renderer, x1, y1);
        }
        return;
    }
    
    float m = (float) (y2 - y1) / (x2 - x1);
    float n = 0;
    
    printf("m: %f\n", m);
    
    for (; x1 != x2 && y1 != y2 ;) {
        
        x1 < x2? x1++ : x1--;
        n += m;
        
        int c = abs(n);
        
        
        for (int i = 0; i <= c; i++) {
            
            if (n >= 1) {
                y1++;
                n--;
            }
            
            if (n <= 1) {
                y1--;
                n++;
            }
            
            SDL_RenderDrawPoint(renderer, x1, y1);
        }
    }
}

inline double deg_to_rad(double deg){
    return deg * (M_PI/180);
}

void draw_circle_A(SDL_Renderer* renderer, int x, int y, double r){
    for (int i = 0; i < 360; i++) {
        double rad = deg_to_rad(i);
        double y_off = sin(rad) * r;
        double x_off = cos(rad) * r;
        SDL_RenderDrawPoint(renderer, x + x_off, y + y_off);
    } // (A)
};

void draw_circle_B(SDL_Renderer* renderer, int x, int y, double r, int step = 45){
    
    int deg45_x_off = static_cast<int>(sin(deg_to_rad(step)) * r);
    
    for (int i = 0; i <= deg45_x_off ; i++) {
        double offset = sqrt(r*r - i*i);
        SDL_RenderDrawPoint(renderer, x + i, y + offset);
        SDL_RenderDrawPoint(renderer, x - i, y - offset);
        SDL_RenderDrawPoint(renderer, x + i, y - offset);
        SDL_RenderDrawPoint(renderer, x - i, y + offset);
        SDL_RenderDrawPoint(renderer, x + offset, y + i);
        SDL_RenderDrawPoint(renderer, x - offset, y - i);
        SDL_RenderDrawPoint(renderer, x + offset, y - i);
        SDL_RenderDrawPoint(renderer, x - offset, y + i);
    }
};

void draw_fill_circle(SDL_Renderer* renderer, int x, int y, double r, int d = 45) {
    for (int i = -r; i <= r ; i++) {
        double offset = sqrt(r*r - i*i);
        draw_line(renderer, x - offset, y + i, x + offset, y + i);
    }
}

void draw_rect(SDL_Renderer* renderer, int x, int y, int w, int h) {
    if (w < 1 || h < 1) return;
    int x2 = x + w - 1, y2 = y + h - 1;
    draw_line(renderer, x, y, x2, y); // t
    draw_line(renderer, x, y, x, y2); // l
    draw_line(renderer, x2, y, x2, y2); // r
    draw_line(renderer, x, y2, x2, y2); // b
}

void draw_fill_rect(SDL_Renderer* renderer, int x, int y, int w, int h) {
    
    for (int j = 0; j < h; j++) {
        for (int i = 0; i < w; i++) {
            SDL_RenderDrawPoint(renderer, x+i, y+j);
        }
    }
}

void draw_triangle(SDL_Renderer* renderer, int x1, int y1, int x2, int y2, int x3, int y3);
void draw_fill_triangle(SDL_Renderer* renderer, int x1, int y1, int x2, int y2, int x3, int y3);

void draw_axis(SDL_Renderer* renderer){
    draw_line(renderer, SCREEN_W/2, 0, SCREEN_W/2, SCREEN_H);
    draw_line(renderer, 0, SCREEN_H/2, SCREEN_W, SCREEN_H/2);
}

void draw_qradratic_graph(SDL_Renderer* renderer, double a, double b, double c) {
    int offset_x = SCREEN_W/2;
    int offset_y = SCREEN_H/2;
    double ratio = 50;
    int last_y = 0;
    for (int i = -1; i < SCREEN_W; i++) {
        
        double x = (i - offset_x) / ratio; // << to graph space
        double y = a * x * x + b * x +c;
        y = -y * ratio + offset_y; // << change back to screen space
        if (i >= 0){
            SDL_RenderDrawLine(renderer, i, last_y, i + 1, y);
        }
        last_y = y;
    }
}; //ax2 + bx + c << drawline

// snake
// keyboard input https://www.libsdl.org/release/SDL-1.2.15/docs/html/guideinputkeyboard.html

int main(int argc, char* argv[])
{
    Uint32 startTime = 0;
    Uint32 endTime = 0;
    Uint32 delta = 0;
    short fps = 60;
    short timePerFrame = 100; // miliseconds
    if (SDL_Init(SDL_INIT_VIDEO) != 0) return -1;
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    
    if (SDL_CreateWindowAndRenderer(640, 480, 0, &window, &renderer) != 0) return -1;
    SDL_bool done = SDL_FALSE;
    //            int x = 0;
    
//    int d = 0;
    while (!done) {
        if (!startTime) {
            // get the time in ms passed from the moment the program started
            startTime = SDL_GetTicks();
        } else {
            delta = endTime - startTime; // how many ms for a frame
        }
        
        
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE); // Red
                                                                       //                SDL_RenderDrawPoint(renderer, 320, 480);
                                                                       //                SDL_RenderDrawPoint(renderer, 10, 10);
                                                                       //                SDL_RenderDrawPoint(renderer, 200, 400);
#if 0
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE); // Red
        draw_line(renderer, 0, 0, 640, 480); // Downward sloping Dia
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE); // Red
        draw_line(renderer, 10, 10, 200, 400); // Downward sloping Dia, slope > 1;
        draw_line(renderer, 10, 10, 400, 10);
        draw_line(renderer, 10, 10, 10, 400);
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, SDL_ALPHA_OPAQUE); // Yellow
        draw_line(renderer, 0, 240, 640, 240); // Horizontal
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, SDL_ALPHA_OPAQUE); // Blue
        draw_line(renderer, 0, 480, 640, 0); // Upward Sloping Dia
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE); // White
        draw_line(renderer, 320, 0, 320, 480); // Vertical
#endif
        draw_axis(renderer);
        draw_qradratic_graph(renderer, -1, 2, 2);
        //                draw_circle_A(renderer, 320, 240, 200);
        //                draw_circle_B(renderer, 320, 240, 200, d);
        //                SDL_SetRenderDrawColor(renderer, 255, 255, 0, SDL_ALPHA_OPAQUE); // Yellow
        //                draw_fill_circle(renderer, 320, 240, 200, d);
        //                if (d <45) d++;
        //                draw_qradratic_graph(renderer, 1, 3, 1);
        
        
        
        
        //                SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE); // Red
        //                draw_fill_rect(renderer, 320, 240, 100, 200);
        //                SDL_SetRenderDrawColor(renderer, 255, 255, 0, SDL_ALPHA_OPAQUE); // Yellow
        //                draw_rect(renderer, 320, 240, 100, 200);
        ////////////////////////////////////////////////////////////////
        SDL_RenderPresent(renderer);
        
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            
            switch (event.type) {
                case SDL_KEYDOWN:
                    switch( event.key.keysym.sym ){
                        case SDLK_LEFT:
                            printf("<");
                            break;
                        case SDLK_RIGHT:
                            printf(">");
                            break;
                        case SDLK_UP:
                            printf("^");
                            break;
                        case SDLK_DOWN:
                            printf("v");
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
