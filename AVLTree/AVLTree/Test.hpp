//
//  Test.hpp
//  AVLtree
//
//  Created by ChrisLam on 04/04/2021.
//

#pragma once
#include "AVLtree.hpp"

struct Test {
    AVLtree tree;
    static const int NUMS_SIZE = 9;
    const int nums[NUMS_SIZE] = {41, 20, 65, 11, 26, 50, 23, 29, 55};
    
    
    
    void _tree_init(){
        
        for (int i = 0; i < 9; i++) {
            std::cout << "insert " << nums[i] <<"\n";
            tree.root = tree._insert(tree.root, nums[i]);
        }
    }
    
    void test(const char* test_name ){
        std::cout <<"== TEST: " << test_name <<" ==\n";
    }
    
    void left_rotation(){
        test("left_rotation()");
        tree.root = tree.left_rotation(tree.root);
        tree.v_print();
    }
    
    void right_rotation(){
        test("right_rotation()");
        tree.root = tree.right_rotation(tree.root);
        tree.v_print();
    }
    

    void tree_height() {
        dump_var(tree.height(tree.root));
    }
    
    void is_balance(){
        TEST(tree.is_balance(tree.root)==true);
    }
    
    void max_value(){
        dump_var(tree.max_value(tree.root)->value);
    }
    
    void _delete(){
        tree.v_print();
        for (int i : nums) {
            std::cout <<"== delete: "<< tree.root->value <<" ==\n";
            tree.root = tree._delete(tree.root, tree.root->value);
            tree.v_print();
        }
        
        _tree_init();
        tree.v_print();
        for (int i = 0; i < NUMS_SIZE ; i++) {
            const int& num = nums[i];
            std::cout <<"== delete: "<< num <<" ==\n";
            tree.root = tree._delete(tree.root, num);
            tree.v_print();
        }
        
        
        _tree_init();
        for (int i = 0; i < NUMS_SIZE ; i+=2) {
            const int& num = nums[i];
            std::cout <<"== delete: "<< num <<" ==\n";
            tree.root = tree._delete(tree.root, num);
            tree.v_print();
        }
        
        _tree_init();
        for (int i = 1; i < NUMS_SIZE ; i+=2) {
            const int& num = nums[i];
            std::cout <<"== delete: "<< num <<" ==\n";
            tree.root = tree._delete(tree.root, num);
            tree.v_print();
        }
    }
    
    void run(){
//        tree_init();
//        tree_height();
//        is_balance();
//
//        left_rotation();
//        tree_height();
//        is_balance();
        _tree_init();
        _delete();
//        tree.v_print();
//        max_value();
    }
};
