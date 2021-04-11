//
//  Heap.hpp
//  Heap
//
//  Created by ChrisLam on 10/04/2021.
//

#pragma once
#include "common.hpp"
#include <vector>

struct Greater {
    bool operator()(int a, int b) {
        return a > b;
    }
};

struct Less {
    bool operator()(int a, int b) {
        return a < b;
    }
};

template<typename Comp>
class Heap { // MaxHeap
    std::vector<int> _arr;
    
    size_t _parent_idx(const size_t node_idx) const {
        assert(node_idx > 0);
        return (node_idx - 1) / 2;
    }
    
    size_t _left_child(const size_t idx) const {
        return 2 * idx + 1;
    }
    
    size_t _right_child(const size_t idx) const {
        return 2 * idx + 2;
    }
    
    void _reheap_up(const size_t node_idx) {
        size_t idx = node_idx;
        Comp comp;
        while (idx) {
            size_t p_idx   = _parent_idx(idx);
            int& p_value = _arr[p_idx];
            int& node_value = _arr[idx];
            if (!comp(node_value, p_value)) return;
            std::swap(p_value, node_value);
            idx = p_idx;
        }
    }
    
    void _reheap_down(size_t node_idx) {
        size_t idx       = node_idx;
        Comp comp;
        while (idx < _arr.size()) {
            size_t left_idx  = _left_child(idx);
            size_t right_idx = _right_child(idx);
            
            if (left_idx >= _arr.size()) return;
            
            int* curr_value = &_arr[idx];
            int* left_value = left_idx < _arr.size()? &_arr[left_idx] : nullptr;
            int* right_value = right_idx < _arr.size()? &_arr[right_idx] : nullptr;

            if (right_value && !comp(*left_value, *right_value)) {
                if (!comp(*right_value, *curr_value)) return;
                std::swap(*right_value, *curr_value);
                idx = right_idx;
            } else {
                if (!comp(*left_value, *curr_value)) return;
                std::swap(*left_value, *curr_value);
                idx = left_idx;
            }
        }
    }
    
public:
           
    bool insert(const int v){
        _arr.push_back(v);
        _reheap_up(_arr.size() - 1);
        return true;
    }
    
    int pop_head(){
        int v = _arr[0];
        remove_at(0);
        return v;
    }
    
    void remove_at(const int idx) {
        _arr[idx] = std::move(_arr.back());
        _arr.resize(_arr.size() - 1);
        _reheap_down(idx);
    }
    
    size_t size() const {
        return _arr.size();
    }
    
    std::ostream& print(std::ostream& s) const {
        for (int i : _arr) s << i << " ";
        return s << "\n";
    }
};

template<typename Comp>
inline std::ostream& operator << (std::ostream& s, const Heap<Comp>& h){
    return h.print(s);
}
