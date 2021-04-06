//
//  Test.hpp
//  RedBlackTree
//
//  Created by ChrisLam on 04/04/2021.
//

#pragma once
#include "RBtree.hpp"

struct Test {
    RBtree tree;
    
    void tree_init(){
        tree.insert(14);
        tree.insert(12);
        tree.insert(20);
        tree.insert(18);
        tree.insert(23);
        tree.insert(44);
//        tree.insert(3);
//        tree.insert(5);
//        tree.insert(6);
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
        tree_init();
        tree_height();
        is_balance();
        
//        std::cout <<"original tree\n";
//        tree.v_print();
//        left_height();
//        right_height();
        left_rotation();
        tree_height();
//        left_height();
//        right_height();
        is_balance();
        
//        right_rotation();
    }
};
