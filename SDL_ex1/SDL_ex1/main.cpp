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
                x1 < x2? y1++ : y1--;
                n--;
            }
            
            if (n <= -1) {
                x1 < x2? y1-- : y1++;
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

void draw_triangle(SDL_Renderer* renderer, int x1, int y1, int x2, int y2, int x3, int y3){
    
//    SDL_SetRenderDrawColor(renderer, 0, 0, 255, SDL_ALPHA_OPAQUE); // B
    draw_line(renderer, x1, y1, x2, y2); // AB
//    SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE); // R
    SDL_RenderDrawLine(renderer, x2, y2, x3, y3);
//    SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE); // G
    draw_line(renderer, x3, y3, x1, y1);  // AC
};

float triangle_area(int x1, int y1, int x2, int y2, int x3, int y3) {
    return abs((x1*(y2-y3) + x2*(y3-y1) + x3*( y1-y2))/2.0);
}

bool point_inside_tri_area(int x1, int y1, int x2, int y2, int x3, int y3, int x, int y) {
    float A = triangle_area(x1, y1, x2, y2, x3, y3);
    float a1 = triangle_area(x, y, x2, y2, x3, y3);
    float a2 = triangle_area(x1, y1, x, y, x3, y3);
    float a3 = triangle_area(x1, y1, x2, y2, x, y);
    return A == a1 + a2 + a3; // <<--
}

void draw_fill_triangle_inside_tri(SDL_Renderer* renderer, int x1, int y1, int x2, int y2, int x3, int y3) {
    int min_x = std::min(std::min(x1, x2), x3);
    int max_x = std::max(std::max(x1, x2), x3);

    int min_y = std::min(std::min(y1, y2), y3);
    int max_y = std::max(std::max(y1, y2), y3);

    for (int x = min_x; x < max_x; x++) {
        for (int y = min_y; y < max_y; y++) {
            if (point_inside_tri_area(x1, y1, x2, y2, x3, y3, x, y)) {
                SDL_RenderDrawPoint(renderer, x, y);
            }
        }
    }
}

double lerp(int a, int b, double w) {
    return  (b - a) * w + a;
}

void draw_fill_triangle_radiate(SDL_Renderer* renderer, int x1, int y1, int x2, int y2, int x3, int y3) {
    // x2 is the original point
    int dx = abs(x3 - x1);
    int dy = abs(y3 - y1);
    int n = dy > dx? dy : dx;
    n *= 2;
    for (int i = 0; i <= n; i++) {
        double w = (double) i/n;
        int x = lerp(x1, x3, w);
        int y = lerp(y1, y3, w);
        SDL_RenderDrawLine(renderer, x2, y2, x, y);
    }
}



void draw_fill_triangle_y_direction_scanline(SDL_Renderer* renderer, int x1, int y1, int x2, int y2, int x3, int y3){
    struct Helper {
        static void draw_fill_flat_triangle(SDL_Renderer* renderer, int x1, int y1, int x2, int y2, int x3, int y3){
            assert(y2 == y3);
            
            
            int dir = y1 > y3? -1 : 1;
            int dy = (y3 - y1) * dir;
            float m2 = (float) (x2 - x1)/(y2 - y1) * dir;
            float m3 = (float) (x3 - x1)/(y3 - y1) * dir;
            float dx2 = x1;
            float dx3 = x1;
            int y = y1;
            for (int i = 0; i <= dy; i++) {
                SDL_RenderDrawLine(renderer, (int) dx2, y, (int) dx3, y);
                y += dir;
                dx2 += m2;
                dx3 += m3;
            }
        }
    };
    
    
    if (y2 < y1) {
        std::swap(y1, y2);
        std::swap(x1, x2);
    }
    
    if (y3 < y1) {
        std::swap(y1, y3);
        std::swap(x1, x3);
    }
    
    if (y3 < y2) {
        std::swap(y2, y3);
        std::swap(x2, x3);
    }
    
//    printf("y1 %i, y2 %i, y3 %i\n", y1, y2, y3);
    
    int y = y2;
    int x = x1 + ((float) (y2 - y1)/(y3 - y1)) * (float) (x3 - x1);
    Helper::draw_fill_flat_triangle(renderer, x1, y1, x2, y2, x, y);
    Helper::draw_fill_flat_triangle(renderer, x3, y3, x2, y2, x, y);
    
//    draw_fill_flat_bottom_triangle(renderer, x1, y1, x2, y2, x, y);
//    draw_fill_flat_top_triangle(renderer, x2, y2, x, y, x3, y3);
}



void draw_axis(SDL_Renderer* renderer){
    draw_line(renderer, SCREEN_W/2, 0, SCREEN_W/2, SCREEN_H);
    draw_line(renderer, 0, SCREEN_H/2, SCREEN_W, SCREEN_H/2);
}

void draw_point(SDL_Renderer* renderer, int x, int y, int size = 8) {
    int half_s = size/2;
    SDL_Rect rect = {x - half_s, y - half_s, size, size};
    SDL_RenderFillRect(renderer, &rect);
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
//        draw_axis(renderer);
//        draw_qradratic_graph(renderer, -1, 2, 2);
        int x1 = SCREEN_W/2;
        int y1 = SCREEN_H/2;
        
        int x2 = x1 + 100;
        int y2 = y1 - 200;
//        int y2 = y1;
        
        int x3 = x1 + 50;
        int y3 = y1 + 100;
        
        
        
        
        
        
        
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE); // White
//        draw_line(renderer, x1, y1, x2, y2);
//        SDL_SetRenderDrawColor(renderer, 0, 0, 255, SDL_ALPHA_OPAQUE); // Blue
        draw_triangle(renderer, x1, y1, x2, y2, x3, y3);
//          draw_fill_flat_bottom_triangle(renderer, x1, y1, x2, y2, x3, y3);
//          draw_fill_flat_top_triangle(renderer, x1, y1, x2, y2, x3, y3);
          draw_fill_triangle_y_direction_scanline(renderer, x1, y1, x2, y2, x3, y3);
//        draw_fill_triangle_radiate(renderer, x2, y2, x1, y1, x3, y3);
//        draw_fill_triangle_radiate(renderer, x1, y1, x2, y2, x3, y3);
//        draw_line(renderer, x2, y2, x1, y1);
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE); // Red
        draw_point(renderer, x1, y1);
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE); // Green
        draw_point(renderer, x2, y2);
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, SDL_ALPHA_OPAQUE); // Blue
        draw_point(renderer, x3, y3);

        
//        SDL_RenderDrawPoint(renderer, x1, y1);
//        SDL_RenderDrawPoint(renderer, x2, y2);
//        SDL_RenderDrawPoint(renderer, x3, y3);
        
        
//        draw_triangle(renderer, x1, y1, x2, y2, x3, y3);
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
