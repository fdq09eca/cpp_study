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

    inline bool         in_range_idx    (const int& idx) const {    return idx >= 0 && idx < len;   }
    inline const int    pointer_to_idx  (const int* p)   const {
        int idx = static_cast<int>(p - data);
        assert(in_range_idx(idx));
        return idx;
    }
    
    

public:
    DynamicArray() = default;

    ~DynamicArray(){
        clean();
    }
    
    DynamicArray(const DynamicArray& arr) {
        *this = arr;
    }
    
    DynamicArray(const int* data, const int& len_) {
        for (int i = 0; i < len_; i++) {
            append(data[i]);
        }
    }
    
    void clean(){
        delete[]  data;
        data    = nullptr;
        len     = 0;
        cap     = 0;
    }
    
    void operator=(const DynamicArray& arr) {
        clean();
        append(arr);
    }
    
    
    void reserve(const int& request_len){
        if (request_len < cap) return;
        
        int     new_cap     = next_pow_of_two(request_len);
        int*    new_data    = new int[new_cap];
        
        if (!new_data)  throw std::runtime_error("new_data allocation failed.\n");
        if (data)       for (int i = 0; i < len; i++) new_data[i] = data[i];
        
        delete[]  data;
        data    = new_data;
        cap     = new_cap;
    };
    
    void resize(const int& new_len){
        reserve(new_len);
        len =   new_len ;
    }
    
    DynamicArray& append(const int& v){
        resize(len + 1);
        data[len - 1] = v;
        return *this;
    }
    
    
    inline const int last_idx() {
        if (!len) return 0;
        return len - 1;
    }
    
    DynamicArray& append(const DynamicArray& arr) {
        assert(arr.data);
        for (int i = 0; i < arr.len; i++) append(arr[i]);
        return *this;
    }
    
    inline const int& get_len() const {
        return len;
    }
    
    const int& get_data(const int idx) const {
        assert(in_range_idx(idx));
        return data[idx];
    }
    
    const int& operator[](const int idx) const {
        return get_data(idx);
    }
    
    bool operator==(const DynamicArray& arr) const {
        int arr_len = arr.get_len();
        if (arr_len != len) return false;
        for (int i = 0; i < len; i++) {
            if (data[i] != arr[i]) return false;
        }
        return true;
    }
    
    const DynamicArray& operator+(const DynamicArray& arr) const {
        return DynamicArray(*this).append(arr); 
    }
    
    const int* local_min(const int& from_idx, const int& to_idx) const {
        assert(in_range_idx(from_idx));
        assert(in_range_idx(to_idx));
        int* min = data + from_idx;
        for (int i = from_idx + 1; i <= to_idx; i++) {
            int* v = &data[i];
            if (*min > *v) min = v;
        }
        return min;
    }
    
    const int* local_max(const int& from_idx, const int& to_idx) const {
        assert(in_range_idx(from_idx));
        assert(in_range_idx(to_idx));
        int* max = data + from_idx;
        for (int i = from_idx + 1; i <= to_idx; i++) {
            int* v = &data[i];
            if (*max < *v) max = v;
        }
        return max;
    }
    
    DynamicArray& sort() {
        for (int i = 0; i < len; i ++){
            int* min = const_cast<int*>(local_min(i, last_idx()));
            std::swap(data[i], *min);
        }
        return *this;
    }
    
    const int* search(const int& v) const {
        
        int* s = data;
        int* e = data + len - 1;
        while (s <= e) {
            int* m = s + static_cast<int>(e - s) / 2;
            if (*m < v) {
                s = m + 1;
                continue;
            }
            if (*m > v){
                e = m - 1;
                continue;
            }
            return m;
        }
        return nullptr; // return the a pointer for insert instead of null?
    }
    
    DynamicArray& del(const int& v) {
        int* p = const_cast<int*>(search(v));
        if (!p) return *this;
        int* end = data + len;
        for (int* next = p + 1; next < end; p++, next++) {
            *p = *next;
        }
        len--;
        return *this;
    }
    
    void insert_before(const int& idx, const int& v) {
        resize(len + 1);
        int num_elements_to_move = len - idx;
        for (int i = 0; i < num_elements_to_move; i++) {
            int last_idx = len - i - 1;
            int last_2nd_idx = last_idx - 1;
            data[last_idx] = data[last_2nd_idx];
        }
        data[idx] = v;
    }
};


inline std::ostream &operator<<(std::ostream &s, DynamicArray &arr)
{
    int len     = arr.get_len();
    int max_idx = len - 1;
    
                            s << "{";
    for (int i = 0; i < len; i++)   {
                            s << arr[i];
        if (i < max_idx)    s << ", ";
    }
                            s << "}\n";
    return s;
};

#endif /* DynamicArray_hpp */
