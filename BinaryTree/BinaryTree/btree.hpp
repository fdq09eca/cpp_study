//
//  btree.hpp
//  BinaryTree
//
//  Created by ChrisLam on 01/04/2021.
//

#pragma once
#include "common.hpp"

struct Node {
    Node* left = nullptr;
    Node* right = nullptr;
    int value = 0;
    
    
    Node(const int v) {
        value = v;
    }
    
    ~Node(){
        std::cout << "delete node val: " << value << "\n";
        delete left;
        delete right;
        clear();
    }
    
    void clear(){
        left = nullptr;
        right = nullptr;
        value = 0;
    }
    
    
    
    
};

struct Tree {
    Node* root = nullptr;
    Tree() = default;
    
    ~Tree() {
        delete root;
    }
    
    Node* insert(Node* node, const int v) {
        if (!node)              return new Node(v);
        if (v > node->value)    node->right =  insert(node->right, v);
        if (v < node->value)    node->left  =  insert(node->left, v);
        return node;
    }
    
    Tree& insert(const int v) {
        root = insert(root, v);
        return *this;
    }
    
   
//    Tree& insert(const int v) {
//        Node** p = &root;
//        while (*p) {
//            if (v == (*p)->value)  return *this;
//
//            if (v > (*p)->value) {
//                p = &((*p)->right);
//                continue;
//            }
//
//            if (v < (*p)->value) {
//                p = &((*p)->left);
//                continue;
//            }
//        }
//        *p = new Node(v);
//        if (!*p) throw std::bad_alloc();
//
//        return *this;
//    }
    
    
    
    Node* find(float v) {
        Node* p = root;
        return p;
    };
    
    
};

