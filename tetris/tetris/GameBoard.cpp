//
//  GameBoard.cpp
//  tetris
//
//  Created by ChrisLam on 02/04/2021.
//

#include "GameBoard.hpp"

GameBoard::GameBoard() {
    for (int y = 0; y < height; y ++) {
        for (int x = 0; x < width; x++) {
            get(x, y).set_pos(x, y);
            get(x, y).set_color(background_color);
        }
    }
    set_line(19, 1);
    set_line(18, 1);
};

Cell& GameBoard::get(const int x, const int y){
    return board[y * width + x];
}

void GameBoard::set(const int x, const int y, const int v) {
board[y * width + x].value = v;
}

void GameBoard::set_piece(Tetrimino piece) {
    for (int y = 0; y < piece.height; y ++) {
        for (int x = 0; x < piece.width; x ++) {
            Cell& cell = piece.get_cell(x, y);
            if (!cell.value) continue;
            set(cell.pos.x, cell.pos.y, cell.value);
        }
    }
}

bool GameBoard::is_line(int y) {
    assert(y >= 0 && y < GameBoard::height);
    for (int x = 0; x < GameBoard::width; x++) {
        Cell& cell = get(x, y);
        if (!cell.value) return false;
    }
    return true;
}

void GameBoard::set_line(int y, int v) {
    assert(y >= 0 && y < GameBoard::height);
    for (int x = 0; x < GameBoard::width - 1; x++) {
        Cell& cell = get(x, y);
        cell.value = v;
    }
}

void GameBoard::remove_lines_until(int dst_y) {
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

void GameBoard::draw(SDL_Renderer* renderer) {
    for (int y = 0; y < height; y++ ){
        for (int x = 0; x < width; x++ ){
            Cell& cell = get(x, y);
            cell.value? cell.set_color(BLUE):cell.set_color(WHITE);
            cell.draw(renderer, offset_x, offset_y);
        }
    }
}
