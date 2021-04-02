//
//  btree.hpp
//  BinaryTree
//
//  Created by ChrisLam on 01/04/2021.
//

#pragma once
#include "common.hpp"
#include <stdlib.h>
#define CHRIS_VER 1

struct Node {
    Node* left = nullptr;
    Node* right = nullptr;
    int key;
    char* value;
    
    
    Node(const int k, const char* v) {
        key = k;
        value = strdup(v);
    }
    
    ~Node(){
        std::cout << "delete node val: " << value << "\n";
        delete left;
        delete right;
        clear();
    }
    
    void clear() {
        left = nullptr;
        right = nullptr;
        free(value);
        key = 0;
        value = nullptr;
    }
    
    void print() {
        std::cout << key << ":" << "[" << value << "]" << "\n";
        if (left) {
            std::cout << key <<" - <L> ";
            left->print();
        }
        if (right) {
            std::cout << key <<" - <R> ";
            right->print();
        }
    }
};

struct Tree {
    Node* root = nullptr;
    Tree() = default;
    
    ~Tree() {
        delete root;
    }
#if CHRIS_VER
    Tree& insert(const int k, const char* c) {
        Node** p = &root;
        while (*p) {
            if (k == (*p)->key)  return *this;

            if (k > (*p)->key) {
                p = &((*p)->right);
                continue;
            }

            if (k < (*p)->key) {
                p = &((*p)->left);
                continue;
            }
        }
        *p = new Node(k, c);
        if (!*p) throw std::bad_alloc();

        return *this;
    }
    
#else
    
    Node* insert(Node* node, const int k, const char* c) {
        if (!node)              return new Node(k, c);
        if (k > node->key)    node->right =  insert(node->right, k, c);
        if (k < node->key)    node->left  =  insert(node->left, k, c);
        return node;
    }

    Tree& insert(const int k, const char* c) {
        root = insert(root, k, c);
        return *this;
    }
    
#endif
    
    Node* find(int k) {
        Node* p = root;
        while (p) {
            if (k == p->key) return p;
            if (k > p->key) {
                p = p->right;
                continue;
            }
            if (k < p->key) {
                p = p->left;
                continue;
            }
        }
        return p;
    };
    
    void print(){
        std::cout << "root: ";
        root->print();
    }
};

