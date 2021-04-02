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
//        tree.root = tree.insert(tree.root, 4);
//        tree.root = tree.insert(tree.root, 3);
//        tree.root = tree.insert(tree.root, 5);
        tree.insert(4);
        tree.insert(3);
        tree.insert(5);
    }
    
    void run(){
        insert();
    }
};
