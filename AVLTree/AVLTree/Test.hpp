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
    
    void tree_init(){
        tree.insert(14);
        tree.insert(12);
        tree.insert(20);
        tree.insert(18);
        tree.insert(23);
        tree.insert(44);
    }
    
    void _tree_init(){
//        tree.root = tree._insert(tree.root, 14);
//        tree.root = tree._insert(tree.root, 12);
//        tree.root = tree._insert(tree.root, 20);
//        tree.root = tree._insert(tree.root, 18);
//        tree.root = tree._insert(tree.root, 23);
//        tree.root = tree._insert(tree.root, 44);
        int nums[] = {41, 20, 65, 11, 26, 50, 23, 29, 55};
        for (int i: nums) {
            tree.root = tree._insert(tree.root, i);
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
    
    void run(){
//        tree_init();
//        tree_height();
//        is_balance();
//
//        left_rotation();
//        tree_height();
//        is_balance();
        _tree_init();
        tree.v_print();
    }
};
