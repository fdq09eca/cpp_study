//
//  btree.hpp
//  BinaryTree
//
//  Created by ChrisLam on 01/04/2021.
//

#pragma once
#include "common.hpp"
#define CHRIS_VER 1

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
#if CHRIS_VER
    Tree& insert(const int v) {
        Node** p = &root;
        while (*p) {
            if (v == (*p)->value)  return *this;

            if (v > (*p)->value) {
                p = &((*p)->right);
                continue;
            }

            if (v < (*p)->value) {
                p = &((*p)->left);
                continue;
            }
        }
        *p = new Node(v);
        if (!*p) throw std::bad_alloc();

        return *this;
    }
    
#else
    
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
    
#endif
    
    Node* find(int v) {
        Node* p = root;
        while (p) {
            if (p->value == v) return p;
            if (v > p->value) {
                p = p->right;
                continue;
            }
            if (v < p->value) {
                p = p->left;
                continue;
            }
        }
        return p;
    };
};

