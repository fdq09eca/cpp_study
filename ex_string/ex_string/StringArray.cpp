//
//  StringArray.cpp
//  ex_string
//
//  Created by ChrisLam on 12/02/2021.
//

#include "StringArray.hpp"
#include "my_common.h"

StringArray::StringArray(const StringArray& arr): _len(0), _cap(0), _data(nullptr){
    *this = arr;
}

StringArray::~StringArray(){
    delete[] _data;
    _data = nullptr;
    _len = 0;
    _cap = 0;
}

void StringArray::operator=(const StringArray& arr){
    resize(arr._len);
    for (size_t i = 0; i < arr._len; i++) {
        _data[i] = arr._data[i]; // overrided opterator =;
    }
}

void StringArray::append(const char* s){
    resize(_len + 1);
    _data[_len - 1] = s;
}

void StringArray::append(const String &str) {
    resize(_len + 1);
    _data[_len - 1] = str;
}

void StringArray::append_move(String &str) {
    resize(_len + 1);
    _data[_len - 1].move(str);
}

void StringArray::reserve(size_t request_len) {
    if (request_len <= _cap) return;
    size_t new_cap = next_pow_of_two(request_len);
    String* new_data = new String[new_cap];
    
    //    memcpy(new_data, _data, _len * sizeof(String));
    for (size_t i = 0; i < _len; i++) {
        new_data[i] = _data[i];
    }
    delete[] _data;
    _data = new_data;
    _cap = new_cap;
}

void StringArray::resize(size_t new_len) {
    reserve(new_len);
    _len = new_len;
}

void test_StringArray(){
    String s("Hello");
    StringArray str_arr;
    str_arr.append(s);
    str_arr.append_move(s); // ownership transfer -> performance boost
    TEST(s == "");
    TEST(str_arr[0] == "Hello");
    TEST(str_arr[1] == "Hello");
    dump_var(str_arr);
    
    str_arr.append("World!!");
    TEST(str_arr[2] == "World!!");
    dump_var(str_arr);
}
