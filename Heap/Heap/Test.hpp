//
//  Test.hpp
//  Heap
//
//  Created by ChrisLam on 10/04/2021.
//

#pragma once
#include "Heap.hpp"



struct Test {
    Heap<Less> heap;
    
    Test(){
        int arr[] = {9, 5, 6, 3, 7, 2, 1, 0, 8, 4};
        for (int v : arr) {
            heap.insert(v);
        }
    }
    
    void run(){
        std::cout << heap;
        while (heap.size()) {
            dump_var(heap.pop_head());
            std::cout << heap;
        }
    }
};
