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
    
    void height(){
        test("height()");
        dump_var(tree.height());
    }
    
    void min_key(){
        test("min_key()");
        dump_var(tree.min_key());
    }
    
    void max_key(){
        test("max_key()");
        dump_var(tree.max_key());
    }
    
    void v_print(){
        test("v_print()");
        tree.v_print();
    }
    
    void run(){
        test("insert()");
//        init_tree();
        
        tree.insert(25, "Eva");
        tree.insert(20, "Eva");
        tree.insert(30, "Eva");
        tree.insert(19, "Eva");
        tree.insert(26, "Eva");
        
//        tree.insert(15, "Bob");
//        tree.insert(19, "Dave");
//        tree.insert(22, "Bob");
//
//
//        tree.insert(18, "Chris");
//        tree.insert(12, "Eva");
//        tree.insert(13, "Amy");
//
//        tree.insert(20, "Eva");
//        tree.insert(15, "Bob");
//        tree.insert(1, "Amy");
        
        
//        tree.insert(21, "Amy");
//        tree.insert(23, "Chris");
//        tree.insert(24, "Dave");
        
//        TEST(tree.min_key()->key == 3);
//        TEST(tree.max_key()->key == 7);
//        height();
//        v_print();
//        tree.print_tree();
//        tree.deep_first_print();
//        tree.min_sort_print();
        tree.max_sort_print();
        dump_var(tree.node_count(tree.root));
        
//        find();
//        print();
        
    }
};
