//
//  AVLtree.hpp
//  AVLtree
//
//  Created by ChrisLam on 04/04/2021.
//
#pragma once
#include "Node.hpp"

struct AVLtree {
    Node* root = nullptr;
    
    AVLtree() = default;
    
    ~AVLtree() {
        delete root;
    }
    
    
    
    Node* insert(Node* node, int v) {
        if (!node) return new Node(v);
        if (v > node->value) node->right = insert(node->right, v);
        if (v < node->value) node->left  = insert(node->left, v);
        return node;
    }
    
    Node* _insert(Node* node, int v) {
        if (!node) return new Node(v);
        if (v > node->value) node->right = _insert(node->right, v);
        if (v < node->value) node->left  = _insert(node->left, v);
        
        int bal = height(node->left) - height(node->right);
        
        bool LH = bal > 1;
        bool RH = bal < -1;
        
        if (LH) node = _left_balance(node);
        if (RH) node = _right_balance(node);
        
        return node;
    }
    
    Node* _left_balance(Node* root) {
        Node* left_child = root->left;
        
        int bal = height(left_child->left) - height(left_child->right);
        
        bool LL = bal >= 1;
        bool LR = bal <= -1;
        
        if (LL) return right_rotation(root);
        
        if (LR) {
            root->left = left_rotation(left_child);
            return right_rotation(root);
        }
        assert("_left_balance failed.\n");
        return nullptr;
    }
    
    Node* _right_balance(Node* root) {
        Node* right_child = root->right;
        
        int bal = height(right_child->left) > height(right_child->right);
        
        bool RL = bal >= 1;
        bool RR = bal <= -1;
        
        if (RR) return left_rotation(root);
        
        if (RL) {
            root->right = right_rotation(right_child);
            return left_rotation(root);
        }
        assert("_right_balance failed.\n");
        return nullptr;
    }
    
    int height(Node* node) {
        if (!node) return 0;
        return std::max(height(node->left), height(node->right)) + 1;
    }
    
    AVLtree& insert(int v) {
        root = insert(root, v);
        return *this;
    }
    
        
    bool is_balance(Node* node) {
        return std::abs(height(node->left) - height(node->right)) <= 1;
    }
    
    Node* left_rotation(Node* old_root) {
        if (!old_root) return old_root;
        
        Node* new_root = old_root->right;
        old_root->right = new_root->left;
        new_root->left = old_root;
        
        return new_root;
    }
    
    Node* right_rotation(Node* old_root) {
        if (!old_root) return old_root;
        
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
