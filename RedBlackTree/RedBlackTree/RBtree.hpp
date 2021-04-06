//
//  RBtree.hpp
//  RedBlackTree
//
//  Created by ChrisLam on 04/04/2021.
//
#pragma once
#include "Node.hpp"

struct RBtree {
    Node* root = nullptr;
    
    RBtree() = default;
    
    ~RBtree() {
        delete root;
    }
    
    Node* insert(Node* node, int v, Color c=RED) {
        if (!node) return new Node(v, c);
        if (v > node->value) node->right = insert(node->right, v, c);
        if (v < node->value) node->left  = insert(node->left, v, c);
        return node;
    }
    
//    int left_height(Node* node) {
//        if (!node) return 0;
//        return left_height(node->left) + 1;
//    }
//
//    int right_height(Node* node) {
//        if (!node) return 0;
//        return right_height(node->right) + 1;
//    }
    
    int height(Node* node) {
        if (!node) return 0;
        return std::max(height(node->left), height(node->right)) + 1;
    }
    
    RBtree& insert(int v) {
        root = insert(root, v, root? RED:BLACK);
        return *this;
    }
    
    Node* left_rotation(Node* old_root) {
        if (!old_root || !old_root->right->right) return old_root;
        
        Node* new_root = old_root->right;
        old_root->right = new_root->left;
        new_root->left = old_root;
        
        return new_root;
    }
    
    bool is_balance(Node* node) {
        return std::abs(height(node->left) - height(node->right)) <= 1;
    }
    
    Node* right_rotation(Node* old_root) {
        if (!old_root || !old_root->left->left) return old_root;
        
        Node* new_root = old_root->left;
        old_root->left = new_root->right;
        new_root->right = old_root;
        
        return new_root;
    }
    
    void v_print(Node* node, int indent, const char* prefix) {
        if (!node) return;
        for (int i = 0; i < indent; i ++) {
            std::cout << "  ";
        }
        std::cout << prefix;

        std::cout << "[" << node->value <<"]\n";
        v_print(node->left, indent + 1, "L:");
        v_print(node->right, indent + 1, "R:");
    }
    
    void v_print(){
        v_print(root, 0, "");
    }
    
};
