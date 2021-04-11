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
#include "common.hpp"

template <typename T>
class DynamicArray {
private:
    T*      data    = nullptr;
    int     len     = 0;
    int     cap     = 0;
    
    bool    in_range_idx(int idx) const {    return idx >= 0 && idx < len;   }
    
    
public:
    DynamicArray() = default;

    ~DynamicArray(){
        clean();
    }
    
    DynamicArray<T>(const DynamicArray<T>& arr) {
        *this = arr;
    }
    
    DynamicArray(const T* data, const int& len_) {
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
    
    void operator= (const DynamicArray<T>& arr) {
        clean();
        append(arr);
    }
    
    
    void reserve(const int& request_len){
        if (request_len < cap) return;
        
        int     new_cap     = next_pow_of_two(request_len);
        T*    new_data    = new T[new_cap];
        
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
    
    int     last_idx()  const { return len - 1; }
    int     get_len()   const { return len; }
    
    DynamicArray& append(const T& v){
        resize(len + 1);
        data[len - 1] = v;
        return *this;
    }
    
    DynamicArray& append(const DynamicArray& arr) {
        assert(arr.data);
        for (int i = 0; i < arr.len; i++)
            append(arr[i]);
        return *this;
    }
    
    DynamicArray& append_range(const T* data, const int len){
        for (int i = 0; i < len; i++ )
            append(data[i]);
        return *this;
    }

    const T& get_data(const int idx) const {
        assert(in_range_idx(idx));
        return data[idx];
    }

    const T& operator[](const int idx) const {
        return get_data(idx);
    }
    
    T& operator[](const int idx){
        return const_cast<T&>(get_data(idx));
    }
    
    
    template<class Y>
    bool operator   == (const DynamicArray<Y>& arr) const {
        if (arr.get_len() != len) return false;
        for (int i = 0; i < len; i++) {
            if (data[i] != arr[i]) return false;
        }
        return true;
    }
    
    bool operator == (const DynamicArray<float>& arr) const {
        if (arr.get_len() != len) return false;
        for (int i = 0; i < len; i++) {
            if (!float_eq(data[i], arr[i])) return false;
        }
        return true;
    }
    
    
    bool operator != (const DynamicArray& arr) const {
        return !(*this == arr);
    }
    
    
    template<class Y>
    DynamicArray<Y> operator+(const DynamicArray<Y>& arr) const {
        return DynamicArray<Y>(*this).append(arr);
    }
    
    const T* local_min(const int& from_idx, const int& to_idx) const {
        assert(in_range_idx(from_idx));
        assert(in_range_idx(to_idx));
        T* min = data + from_idx;
        for (int i = from_idx + 1; i <= to_idx; i++) {
            T* v = &data[i];
            if (*min > *v) min = v;
        }
        return min;
    }

   
    const T* local_max(const int from_idx, const int to_idx) const {
        assert(in_range_idx(from_idx));
        assert(in_range_idx(to_idx));
        T* max = data + from_idx;
        for (int i = from_idx + 1; i <= to_idx; i++) {
            T* v = &data[i];
            if (*max < *v) max = v;
        }
        return max;
    }
    

    DynamicArray& sort() {
        for (int i = 0; i < len; i ++){
            T* min = const_cast<T*>(local_min(i, last_idx()));
            std::swap(data[i], *min);
        }
        return *this;
    }

    const T* search(const T& v) const {
        if (!data || len <= 0) return nullptr;

        T* s = data;
        T* e = data + len - 1;
        while (s <= e) {
            T* m = s + static_cast<ptrdiff_t>(e - s) / 2;
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

    DynamicArray& del(const T& v) {
        T* p = const_cast<T*>(search(v));
        if (!p) return *this;
        T* end = data + len;
        for (T* next = p + 1; next < end; p++, next++) {
            *p = *next;
        }
        len--;
        return *this;
    }

    void insert_at(const int& idx, const T& v) {
        resize(len + 1);
        int num_elements_to_move = len - idx;
        for (int i = 0; i < num_elements_to_move; i++) {
            int last_idx_ = last_idx() - i;
            int last_2nd_idx = last_idx_ - 1;
            data[last_idx_] = data[last_2nd_idx];
        }
        data[idx] = v;
    }
};


template<typename T>
inline std::ostream &operator<<(std::ostream &s, DynamicArray<T> &arr)
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
