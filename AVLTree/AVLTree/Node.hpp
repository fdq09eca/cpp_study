//
//  Node.hpp
//  AVLtree
//
//  Created by ChrisLam on 04/04/2021.
//
#pragma once
#include "common.hpp"

enum Color {NONE, RED, BLACK};

struct Node {
    int value = 0;
    Node* left = nullptr;
    Node* right = nullptr;
    
    Node(int v):value(v){};
    
    ~Node() {
        delete left;
        delete right;
        cleanup();
    }
    
    void cleanup(){
        left = nullptr;
        right = nullptr;
        value = 0;
    }
    
};
