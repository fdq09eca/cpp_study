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
        tree.insert(4);
        tree.insert(3);
        tree.insert(5);
        TEST(tree.find(4) != nullptr);
        TEST(tree.find(6) == nullptr);
    }
    
    void run(){
        insert();
    }
};
