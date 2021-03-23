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
SDL_Color WHITE = {255, 255, 255, 255};
SDL_Color BLACK = {0, 0, 0, 255};
SDL_Color RED = {255, 0, 0, 255};
SDL_Color BLUE = {0, 0, 255, 255};

struct Point{
    int x;
    int y;
    Point(){};
    Point(int x_, int y_): x(x_), y(y_){};
};


struct Cell {
    static const int size = 20;
    Point pos;
    SDL_Color color;
    SDL_Color border_color = BLACK;
    int value = 0;
    
    Cell(){};
    
    
    void set_pos(int x_, int y_) {
        pos.x = x_;
        pos.y = y_;
    }
    
    void set_color(SDL_Color color_) {
        color = color_;
    }
    
    
    void draw(SDL_Renderer* renderer, int offset_x = 5, int offset_y = 5) {
        SDL_Rect rect = { (pos.x + offset_x) * size,
                          (pos.y + offset_y) * size,
                           size, size
                        };

        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_RenderFillRect(renderer, &rect);

        SDL_SetRenderDrawColor(renderer, border_color.r, border_color.g, border_color.b, border_color.a);
        SDL_RenderDrawRect(renderer, &rect);
    }
    
};

struct Tetrimino {
    static const int width = 4;
    static const int height = 4;
    Point pos;
    Cell data[width * height];
    
    Tetrimino(){};
    
    void init(int* data_, int x_, int y_){
        pos.x = x_;
        pos.y = y_;
        for (int x = 0; x < width; x++) { // x is col
            for (int y = 0; y < height; y++) { // y is row
                int i = y * width + x; //
                Cell& cell = data[i];
                int v = data_[i];
                cell.value = v;
                cell.set_pos(pos.x + x, pos.y + y);
                if (!cell.value) continue;
                cell.color = RED;
            }
        }
    }
    
    void move(int x, int y) {
        pos.x += x;
        pos.y += y;
    }
    
    void set_data(int* data_) {
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                int i = y * width + x;
                data[i].value = data_[i];
            }
        }
    }
    
    void counter_rotate() {
        int new_data[width*height];
        
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                int dst_y = height - x - 1;
                int dst_x = y;
                new_data[dst_y * width + dst_x] = get_cell(x, y).value;
            }
        }
        set_data(new_data);
    }
    
    void rotate() {
        int new_data[width*height];
        
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                int dst_y = x;
                int dst_x = height - y - 1;
                new_data[dst_y * width + dst_x] = get_cell(x, y).value;
            }
        }
        set_data(new_data);
    }
    
    Cell& get_cell(int x, int y){
        return data[y * width + x];
    }
    
    void draw(SDL_Renderer* renderer) {
        for (int x = 0; x < width; x++) { // x is col
            for (int y = 0; y < height; y++) { // y is row
                Cell& cell = get_cell(x, y);
                cell.set_pos(pos.x + x, pos.y + y);
                if (!cell.value) continue;
                cell.color = RED;
                cell.draw(renderer);
            }
        }
    }
};


struct GameBoard {
    static const int width = 10;
    static const int height = 20;
    static const int offset_x = 5;
    static const int offset_y = 5;
    
    SDL_Color background_color = WHITE;
    Cell board[width * height];

    GameBoard() {
        for (int y = 0; y < height; y ++) {
            for (int x = 0; x < width; x++) {
                get(x, y).set_pos(x, y);
                get(x, y).set_color(background_color);
            }
        }
        set_line(19, 1);
        set_line(18, 1);
    };
    
    Cell& get(const int x, const int y){
        return board[y * width + x];
    }
    
    void set(const int x, const int y, const int v) {
        board[y * width + x].value = v;
    }
    
    void set_piece(Tetrimino piece) {
        for (int y = 0; y < piece.height; y ++) {
            for (int x = 0; x < piece.width; x ++) {
                Cell& cell = piece.get_cell(x, y);
                if (!cell.value) continue;
                set(cell.pos.x, cell.pos.y, cell.value);
            }
        }
    }
    
    
    bool is_line(int y) {
        assert(y >= 0 && y < GameBoard::height);
        for (int x = 0; x < GameBoard::width; x++) {
            Cell& cell = get(x, y);
            if (!cell.value) return false;
        }
        return true;
    }
    
    void set_line(int y, int v) {
        assert(y >= 0 && y < GameBoard::height);
        for (int x = 0; x < GameBoard::width - 1; x++) {
            Cell& cell = get(x, y);
            cell.value = v;
        }
    }
    
    void remove_lines_until(int dst_y) {
        assert(dst_y >= 0 && dst_y < GameBoard::height);
        
        for (int y = 0; y < dst_y; y++) {
            for (int x = 0; x < GameBoard::width; x++) {
                int dy = dst_y - y;
                int sy = dy - 1;
                
                assert(dy >= 0 && dy < GameBoard::height);
                assert(sy >= 0 && sy < GameBoard::height);
                Cell& src = get(x, sy);
                set(x, dy, src.value);
            }
        }
    }
    
    void draw(SDL_Renderer* renderer) {
        for (int y = 0; y < height; y++ ){
            for (int x = 0; x < width; x++ ){
                Cell& cell = get(x, y);
                cell.value? cell.set_color(BLUE):cell.set_color(WHITE);
                cell.draw(renderer, offset_x, offset_y);
            }
        }
    }
    
    
};



struct Tetriminos {
    static const int count = 7;
    int shapes[count][Tetrimino::width * Tetrimino::height] = {
        { // T
            0, 1, 0, 0,
            1, 1, 1, 0,
            0, 0, 0, 0,
            0, 0, 0, 0,
        },
        { // O
            1, 1, 0, 0,
            1, 1, 0, 0,
            0, 0, 0, 0,
            0, 0, 0, 0,
        },
        { // I
            0, 1, 0, 0,
            0, 1, 0, 0,
            0, 1, 0, 0,
            0, 1, 0, 0,
        },
        { // L
            0, 1, 0, 0,
            0, 1, 0, 0,
            0, 1, 1, 0,
            0, 0, 0, 0,
        },
        { // J
            0, 1, 0, 0,
            0, 1, 0, 0,
            1, 1, 0, 0,
            0, 0, 0, 0,
        },
        { // S
            0, 1, 1, 0,
            1, 1, 0, 0,
            0, 0, 0, 0,
            0, 0, 0, 0,
        },
        { // Z
            1, 1, 0, 0,
            0, 1, 1, 0,
            0, 0, 0, 0,
            0, 0, 0, 0,
        },
        
    };
    
    Tetrimino tetriminos[count]; // [t1, t2, t3, t4, t5, t6]
    
    Tetriminos() {
        for (int i = 0; i < count ; i++) {
            tetriminos[i].init(shapes[i], 0, 0);
        }
    }
    
    Tetrimino get(int i, int x_ = 0, int y_ = 0) {
        assert(i >= 0 && i < count);
        Tetrimino piece = tetriminos[i];
        piece.pos.x = x_;
        piece.pos.y = y_;
        return piece;
    }
    
    Tetrimino rand_get(int x_ = 0, int y_ = 0) {
        int i = rand() % count;
        return get(i, x_, y_);
    }
    
};
    
struct Player {
    SDL_Renderer* renderer = nullptr;
    GameBoard board;
    Tetrimino curr_piece;
    Tetrimino next_piece;
    Tetriminos pieces;
    Uint32 spwan_time;
    Uint32 cum_time;
    Uint32 time_out = 100;
    
    Player(SDL_Renderer* renderer_):renderer(renderer_){
        next_piece = pieces.rand_get(board.width + 2);
        spawn_curr_piece();
    }
    
    bool is_overlapped(int px, int py, const Tetrimino& piece) {
        Tetrimino tmp = piece;
        tmp.pos.x = px;
        tmp.pos.y = py;
       
        
        for (int y = 0; y < tmp.height; y++) {
            for (int x = 0; x < tmp.width; x++) {
                int i = y * tmp.width + x;
                Cell& cell = tmp.data[i];
                if (cell.value) {
                    cell.set_pos(px + x, py + y);
                    if (cell.pos.x >= GameBoard::width) return true;
                    if (cell.pos.x < 0) return true;
                    if (cell.pos.y >= GameBoard::height) return true;
                    if (cell.pos.y < 0) return true;
                    if (board.get(px + x, py + y).value) return true;
                }
                
            }
        }
        return false;
    }
    
    void clean_line() {
        for (int y = 0; y < curr_piece.height; y++) {
            for (int x = 0; x < curr_piece.width; x++) {
                Cell& p_cell = curr_piece.get_cell(x, y);
                if (!p_cell.value) continue;
                int py = p_cell.pos.y;
                if (board.is_line(py)) {
                    board.remove_lines_until(py);
                }
            }
        }
    }
    
    void move(int dx, int dy) {
        int nx = dx + curr_piece.pos.x;
        int ny = dy + curr_piece.pos.y;
        
        
        if (is_overlapped(nx, ny, curr_piece)) {
            if (dy > 0) {
                board.set_piece(curr_piece);
                clean_line();
                spawn_curr_piece();
            }
            return;
        }
        
        curr_piece.move(dx, dy);
    }
        
    void rotate(){
        Tetrimino tmp = curr_piece;
        tmp.rotate();
        if (is_overlapped(tmp.pos.x, tmp.pos.y, tmp)) return;
        curr_piece.rotate();
    }
    
    void hard_drop(){
        while (!is_overlapped(curr_piece.pos.x, curr_piece.pos.y + 1, curr_piece)) {
            move(0, 1);
        }
        curr_piece.draw(renderer);
        move(0, 1);
    }
    
    void counter_rotate(){
        Tetrimino tmp = curr_piece;
        tmp.counter_rotate();
        if (is_overlapped(tmp.pos.x, tmp.pos.y, tmp)) return;
        curr_piece.counter_rotate();
    }
    
    void spawn_curr_piece(){
        curr_piece = next_piece;
        curr_piece.pos.x = 0;
        curr_piece.pos.y = 0;
        spwan_time = SDL_GetTicks();
        next_piece = pieces.rand_get(board.width + 2);
    }
    
    void render() {
        board.draw(renderer);
        curr_piece.draw(renderer);
        next_piece.draw(renderer);
    }
    
    
    bool update(Uint32 delta_time){
        cum_time += delta_time;
        if (cum_time > time_out) {
            move(0, 1);
            cum_time = 0;
        }
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_KEYDOWN:
                    switch( event.key.keysym.sym ){
                        case SDLK_LEFT:
                            move(-1, 0);
                            break;
                        case SDLK_RIGHT:
                            move(1, 0);
                            break;
                        case SDLK_DOWN:
                            move(0, 1);
                            break;
                        case SDLK_UP:
                            move(0, -1);
                            break;
                        case SDLK_r:
                            rotate();
                            break;
                        case SDLK_1:
                            spawn_curr_piece();
                            break;
                        case SDLK_q:
                            counter_rotate();
                            break;
                        case SDLK_SPACE:
                            hard_drop();
                            break;
                        case SDLK_ESCAPE:
                            return false;
                    }
                    printf( "Key press detected\n" );
                    break;
                
                case SDL_KEYUP:
                    printf( "Key release detected\n" );
                    break;
                    
                case SDL_QUIT:
                    return false;
            }
        }
        return true;
    }
    
};

int main(int argc, const char * argv[]) {
    srand(static_cast<unsigned int>(time(NULL)));
    std::cout << rand() <<"\n";
//    std::cout << rand() <<"\n";
//    std::cout << rand()<<"\n";
//    std::cout << rand()<<"\n";
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
        last_time = curr_time;
        curr_time = SDL_GetTicks();
        delta_time = curr_time - last_time;
        
        if (!player.update(delta_time)) break;
        
        player.render();
//
       
        
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
