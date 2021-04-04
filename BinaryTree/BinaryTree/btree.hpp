//
//  btree.hpp
//  BinaryTree
//
//  Created by ChrisLam on 01/04/2021.
//

#pragma once
#include "common.hpp"
#include <stdlib.h>
#include <iomanip>
#include <vector>
#include <sstream>
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
//        if (value)  std::cout << "delete node val: " << value << "\n";
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
    void deep_first_print() {
        using namespace std;
        struct helper {
            vector<vector<Node*>> rows;
            
            void recur(Node* node, int lv) {
                if (!node) return;
                if (rows.size() <= lv) rows.resize(lv + 1);
                vector<Node*>& curr_row = rows[lv];
                curr_row.push_back(node);
                recur(node->left, lv+1);
                recur(node->right, lv+1);
            }
        };
        helper h;
        h.recur(root, 0);
        for (size_t i = 0, n = h.rows.size(); i < n; i++) {
            size_t lv = n - i - 1;
            for (auto& p: h.rows[lv]) {
                std::cout << p->key << " ";
            }
        }
    }
    
    
    void _min_sort_print(Node* node){
        if (!node) return;
        _min_sort_print(node->left);
        std::cout << node->key << " ";
        _min_sort_print(node->right);
    }
    
    void min_sort_print(){
        _min_sort_print(root);
        std::cout <<"\n";
    }
    
    void _max_sort_print(Node* node){
        if (!node) return;
        _max_sort_print(node->right);
        std::cout << node->key << " ";
        _max_sort_print(node->left);
    }
    
    void max_sort_print(){
        _max_sort_print(root);
        std::cout <<"\n";
    }
    
    
    int node_count(Node* node) {
//        if (!node) return 0;
//        return node_count(node->left) + node_count(node->right) + 1;
        return (node)? node_count(node->left) + node_count(node->right) + 1 : 0;
    }
    
    void print(){
        std::cout << "root: ";
        root->print();
    }
    
    void v_print(Node* node, int indent, const char* prefix) {
        
        if (!node) return;
        for (int i = 0; i < indent; i ++) {
            std::cout << "  ";
        }
        std::cout << prefix;

        std::cout << node->key << "[" << node->value <<"]\n";
        v_print(node->left, indent + 1, "L:");
        v_print(node->right, indent + 1, "R:");
    }
    
    void v_print(){
        v_print(root, 0, "");
    }
    
    void print_tree();
    
};

class Tree_printer{
    std::vector<std::vector<Node*>> m_rows;
//    Tree* m_tree = nullptr;
public:
    Tree_printer(Tree* tree){
        print_row(tree->root, 0);
        for (size_t i = 0, n = m_rows.size(); i < n ;i++) {
            size_t rev_row = n - i;
            
            int interval = (1 << rev_row) - 1;
            //
            for (int i = 0; i < interval / 2; i++) {
                std::cout << "  ";
            }
            
            for (auto& node: m_rows[i]) {
                if (!node) {
                    std::cout << "[__]";
                } else {
                    std::cout << "[" << std::setw(2) << node->key << "]";
                }
                
                // interval
                
                for (int j = 1; j < interval; j++) {
                    std::cout << "  ";
                }
            }
            std::cout << "\n";
        }
    }
    
    void print_row(Node* node, int curr_lv){
        
        if (m_rows.size() <= curr_lv){
            m_rows.resize(curr_lv + 1);
            
            if (curr_lv > 0){
                size_t prev_row = m_rows[curr_lv - 1].size() - 1;
                auto& s = m_rows[curr_lv];
                for (size_t i = 0; i < prev_row * 2; i++) {
                    s.push_back(nullptr);
                }
            }
                        
        }
        
        auto& curr_row = m_rows[curr_lv];
        curr_row.push_back(node);
        if (!node) return;
//        s <<"["<< std::setw(2) << node->key <<"]";
        print_row(node->left , curr_lv + 1);
        print_row(node->right, curr_lv + 1);
    }
       
    
};

inline void Tree::print_tree(){
    Tree_printer(this);
}
