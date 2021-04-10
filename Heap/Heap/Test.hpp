//
//  Test.hpp
//  Heap
//
//  Created by ChrisLam on 10/04/2021.
//

#pragma once
#include "Heap.hpp"

struct Test {
    int arr[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    Heap heap;
    
    void heap_init(){
        heap = Heap(arr, 10);
    }
    
    void heap_stage(){
        for (int i = 0; i < heap.size; i++) {
             std::cout<< "heap.arr[" << i << "]: " << heap.arr[i] <<"\n";
        };
        dump_var(heap.cap);
        dump_var(heap.size);
        dump_var(heap.heap_idx);
    }
    
    void run(){
        heap_init();
        heap_stage();
    }
};
