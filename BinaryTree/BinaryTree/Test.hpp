//
//  Test.hpp
//  BinaryTree
//
//  Created by ChrisLam on 01/04/2021.
//

#pragma once
#include "btree.hpp"

struct Test {
    Tree tree;
    
    void init_tree() {
        tree.insert(4, "Amy");
        tree.insert(3, "Bob");
        tree.insert(5, "Chris");
        tree.insert(6, "Dave");
        tree.insert(7, "Eva");
    }
    
    
    void test(const char* test_name) {
        std::cout << "== TEST: " << test_name <<" ==\n";
    }
    
       
    void find() {
        test("find()");
        TEST(tree.find(4) != nullptr);
        TEST(strcmp(tree.find(4)->value, "Amy") == 0);
        TEST(strcmp(tree.find(6)->value, "Dave") == 0);
        TEST(tree.find(10) == nullptr);
    }
    
    
    
    void print(){
        test("print()");
        tree.print();
    }
    
    void run(){
//        test("insert()");
        init_tree();
        find();
//        print();
    }
};
