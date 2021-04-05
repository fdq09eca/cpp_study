//
//  Node.hpp
//  RedBlackTree
//
//  Created by ChrisLam on 04/04/2021.
//
#pragma once
#include "common.hpp"

enum Color {NONE, RED, BLACK};

struct Node {
    int value = 0;
    Color color = NONE;
    Node* left = nullptr;
    Node* right = nullptr;
    
    Node(int v, Color c = NONE):value(v), color(c){};
    
    ~Node() {
        delete left;
        delete right;
        cleanup();
    }
    
    void cleanup(){
        left = nullptr;
        right = nullptr;
        value = 0;
        color = NONE;
    }
    
    void set_color(Color c) {
        color = c;
    }
};
