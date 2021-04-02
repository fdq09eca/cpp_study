//
//  Test.hpp
//  BinaryTree
//
//  Created by ChrisLam on 01/04/2021.
//

#pragma once
#include "btree.hpp"

struct Test {
    void insert() {
        Tree tree;
        tree.insert(4, "Amy");
        tree.insert(3, "Bob");
        tree.insert(5, "Chris");
        tree.insert(6, "Dave");
        tree.insert(7, "Eva");
        TEST(tree.find(4) != nullptr);
        TEST(strcmp(tree.find(4)->value, "Amy") == 0);
        TEST(strcmp(tree.find(6)->value, "Dave") == 0);
        TEST(tree.find(10) == nullptr);
        tree.print();
    }
    
    void run(){
        insert();
    }
};
