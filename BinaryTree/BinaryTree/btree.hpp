//
//  btree.hpp
//  BinaryTree
//
//  Created by ChrisLam on 01/04/2021.
//

#pragma once
#include "common.hpp"
#include <stdlib.h>
#define RECUR_VER 1

struct Node {
    Node* left = nullptr;
    Node* right = nullptr;
    char* value = nullptr;
    int key;
    
    Node(const int k, const char* c) {
        key = k;
        value = strdup(c);
    }
    
    ~Node(){
        if (value)  std::cout << "delete node val: " << value << "\n";
        delete left;
        delete right;
        clear();
    }
    
    void clear() {
        left = nullptr;
        right = nullptr;
        key = 0;
        if (value) free(value);
        value = nullptr;
    }
    
    void print() {
        std::cout << "\t" <<key << ":" << "[" << value << "]";
        if (left) {
            std::cout << "\n\t\t/";
            if (right) std::cout << "\t\\";
            std::cout << "\n";
            left->print();
        }
        if (right) {
            if (!left) std::cout << "\n\t\t\t\t\\\n";
//            std::cout << key <<" - <R> ";
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
#if RECUR_VER
    Node* insert(Node* node, const int k, const char* c) {
        if (!node)            return new Node(k, c);
        if (k > node->key)    node->right =  insert(node->right, k, c);
        if (k < node->key)    node->left  =  insert(node->left, k, c);
        return node;
    }

    Tree& insert(const int k, const char* c) {
        root = insert(root, k, c);
        return *this;
    }
    
    const Node* find(Node* node, int k) const {
        if (!node)          return nullptr;
        if (k > node->key ) return find(node->right, k);
        if (k < node->key ) return find(node->left, k);
        return node;
    }
    
    const Node* find(const int k) const {
        return find(root, k);
    }
    
//    int height(Node* node, const int curr_height) {
//        if (!node) return curr_height - 1;
//        int right_tree_height = height(node->right, curr_height + 1);
//        int left_tree_height = height(node->left, curr_height + 1);
//        return std::max(right_tree_height, left_tree_height);
//    }
    
//    int height(){
//        return height(root, 0);
//    }
    int height(Node* node) {
        if (!node) return -1;
        int left_h  = height(node->left);
        int right_h  = height(node->right);
        return std::max(left_h, right_h) + 1;
        
    }
    int height(){
        return height(root);
    }
    
    Node* min_key(Node* node) {
        if (!node) return nullptr;
        if (!node->left) return node;
        return min_key(node->left);
    }
    
    Node* min_key() {
        return min_key(root);
    }
    
    Node* max_key(Node* node) {
        if (!node) return nullptr;
        if (!node->right) return node;
        return max_key(node->right);
    }
    
    Node* max_key() {
        return max_key(root);
    }
    
#else
    
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
        std::cout << "Node(" << k << ", " << c <<") inserted.\n";

        return *this;
    }
    
    const Node* find(int k) {
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
#endif
    
    
    
    
    
    void print(){
        std::cout << "root: ";
        root->print();
    }
};

