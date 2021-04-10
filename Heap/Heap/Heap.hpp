//
//  Heap.hpp
//  Heap
//
//  Created by ChrisLam on 10/04/2021.
//

#pragma once
#include "common.hpp"

struct Heap {
    int* arr = nullptr;
    int size = 0;
    int heap_idx = -1;
    int cap = 0;
        
    Heap(int* arr_ = nullptr, const int size_ = 0):size(size_){
        cap = next_pow_of_two(size);
        arr = new int[cap];
        assert(arr);
        if (arr_) {
            for (int i = 0; i < size; i++) {
                arr[i] = arr_[i];
            }
        }
    }
    
    ~Heap() {
        if (arr) delete[] arr;
        size = 0;
        heap_idx = -1;
        cap = 0;
    }
    
    bool heap_full() const{
        return heap_idx >= cap;
    }
    
    bool insert(const int v){
        if (heap_full()) return false;
        heap_idx++;
        size++;
        arr[heap_idx] = v;
        reheap_up(heap_idx);
        
        return true;
    }
    
    int parent_idx(const int node_idx) {
        int p = (node_idx - 1) / 2;
        assert(p >= 0 && p < cap);
        return p;
    }
    
    void reheap_up(const int node_idx) {
        assert(node_idx >= 0 && node_idx < cap);
        if (!node_idx) return; //root
        int p_idx   = parent_idx(node_idx);
//        int p_value =
//
//
    }
    
    int left_child(const int idx) const {
        assert(idx > heap_idx);
        return 2 * idx + 1;
    }
    
    int right_child(const int idx) const {
        assert(idx > heap_idx);
        return 2 * idx + 1;
    }
    
};
