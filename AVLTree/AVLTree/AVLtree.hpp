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
    
    Node* _insert(Node* node, int v) {
        if (!node) return new Node(v);
        if (v > node->value) node->right = _insert(node->right, v);
        if (v < node->value) node->left  = _insert(node->left , v);
        return update(node);
    }
    
    int height(Node* node) {
        if (!node) return 0;
        return std::max(height(node->left), height(node->right)) + 1;
    }
    
    bool is_balance(Node* node) {
        return std::abs(height(node->left) - height(node->right)) <= 1;
    }
    
    Node* update (Node* node) {
        if (!node) return nullptr;
        int bal = height(node->left) - height(node->right);
        
        bool LH = bal >  1;
        bool RH = bal < -1;
        
        if (LH) node = _left_balance(node);
        if (RH) node = _right_balance(node);
        
        return node;
    }
    
    Node* _delete(Node* node, int v) {
        
        if (!node) return nullptr;
        
        if (v != node->value) {
            if (v > node->value) node->right = _delete(node->right, v);
            if (v < node->value) node->left =  _delete(node->left , v);
            return update(node);
        }
        
        Node* del_node = node;
        
        if (!node->left) {
            node = node->right;
            del_node->cleanup();
            delete del_node;
            return update(node);
        }
        
        if (!node->right) {
            node = node->left;
            del_node->cleanup();
            delete del_node;
            return update(node);
        }
        
        if (node->right && node->left) {
            Node* replacement_node = max_value(node->left);
            node->value = replacement_node->value;
            node->left = _delete(node->left, replacement_node->value);
            return update(node);
        }
        
        assert( false && "You should not be here.\n");
        return nullptr;
    }
    
    Node* max_value(Node* node) {
        if (!node) return nullptr;
        return node->right? max_value(node->right) : node;
    }
    
    Node* _left_balance(Node* root) {
        assert(root && "_left_balance failed, root is null.\n");
        
        Node* left_child = root->left;
        int left_height = height(left_child->left);
        int right_height = height(left_child->right);
        
        int bal = left_height - right_height;
        
        bool LL = bal >=  1;
        bool LR = bal <= -1;
        bool EH = bal ==  0;
        
        if (LL) return right_rotation(root);
        
        if (LR || EH) {
            root->left = left_rotation(left_child);
            return right_rotation(root);
        }
        assert("_left_balance failed.\n");
        return nullptr;
    }
    
    Node* _right_balance(Node* root) {
        assert(root && "_right_balance failed, root is null.\n");
        Node* right_child = root->right;
        
        int left_height = height(right_child->left);
        int right_height = height(right_child->right);
        int bal = left_height - right_height;
        
        bool RL = bal >=  1;
        bool RR = bal <= -1;
        bool EH = bal ==  0;
        
        if (RR) return left_rotation(root);
        
        if (RL || EH) {
            root->right = right_rotation(right_child);
            return left_rotation(root);
        }
        assert(false && "_right_balance failed.\n");
        return nullptr;
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

        std::cout << "[" << node->value << "]\n";
        v_print(node->left , indent + 1, "L:")  ;
        v_print(node->right, indent + 1, "R:")  ;
    }
    
    
    void v_print(){
        v_print(root, 0, "");
    }
    
};
