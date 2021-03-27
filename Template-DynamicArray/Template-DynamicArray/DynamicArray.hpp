//
//  DynamicArray.hpp
//  Template-DynamicArray
//
//  Created by ChrisLam on 27/03/2021.
//

#ifndef DynamicArray_hpp
#define DynamicArray_hpp

#include <stdio.h>
#include <iostream>

inline int next_pow_of_two(int n) {
    int    i =  1;
    while (i <  n)
           i *= 2;
    return i;
}

class DynamicArray {
private:
    int*    data    = nullptr;
    int     len     = 0;
    int     cap     = 0;

public:
    DynamicArray() = default;
    
    ~DynamicArray(){
        delete[]  data;
        data    = nullptr;
        len     = 0;
        cap     = 0;
    }
    
    void reserve(int request_len){
        if (request_len < cap) return;
        
        int     new_cap     = next_pow_of_two(request_len);
        int*    new_data    = new int[new_cap];
        
        if (!new_data)  throw std::runtime_error("new_data allocation failed.\n");
        if (data)       for (int i = 0; i < len; i++) new_data[i] = data[i];
        
        delete[]  data;
        data    = new_data;
        cap     = new_cap;
    };
    
    void resize(int new_len){
        reserve(new_len);
        len = new_len;
    }
    
    void append(int v){
        resize(len + 1);
        data[len - 1] = v;
    }
    
    const int& get_len(){
        return len;
    }
    
    const int& get_data(const int idx) const {
        assert(idx >= 0 && idx < len);
        return data[idx];
    }
    
    const int& operator[](const int idx) const {
        return get_data(idx);
    }
    
};


inline std::ostream &operator<<(std::ostream &s, DynamicArray &arr)
{
    int len     = arr.get_len();
    int max_idx = len - 1;
    s << "[";
    for (int i = 0; i < len; i++)
    {
        s << arr[i];
        if (i < max_idx)
        {
            s << ", ";
        }
    }
    s << "]\n";
    return s;
};

#endif /* DynamicArray_hpp */
