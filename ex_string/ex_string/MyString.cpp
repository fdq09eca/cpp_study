//
//  MyString.cpp
//  ex_string
//
//  Created by ChrisLam on 12/02/2021.
//

#include "MyString.hpp"
#include "my_common.h"

String::String() : _len(0), _cap(0), _data(nullptr){}

String::String(const char *s) : _len(0), _cap(0), _data(nullptr) {
    append(s);
}

String::String(const String &str) : _len(0), _cap(0), _data(nullptr) {
    *this = str;
}

String::~String() {
    release();
}

void String::release(){
    delete[] _data;
    _data = nullptr;
    _len = 0;
    _cap = 0;
}

void String::clear() {
    resize(0);
}

void String::operator=(const String &str) {
    clear();
    append(str);
}

void String::reserve(size_t request_len) {
    if (request_len <= _cap) return;
    size_t new_cap = next_pow_of_two(request_len);
    char *new_data = new char[new_cap + 1];
    memcpy(new_data, _data, _len * sizeof(char));
    
    delete[] _data;
    _data = new_data;
    _cap = new_cap;
}

void String::resize(size_t new_len) {
    reserve(new_len);
    _len = new_len;
}

String& String::append(const char *s) {
    if (s == nullptr) return *this;
    size_t s_len = strlen(s);
    size_t old_len = _len;
    size_t new_len = s_len + _len;
    resize(new_len);
    memcpy(_data + old_len, s, s_len * sizeof(char));
    _data[new_len] = 0;
    return *this;
}

String& String::append(const String &str) {
    return append(str._data);
}

void String::operator+=(const char *s) {
    append(s);
}

void String::operator+=(const String &str) {
    append(str);
}

String String::operator+(const char *s) const {
    return String(*this).append(s);
}

String String::operator+(const String &str) const {
    return String(*this).append(str);
}

size_t String::len() const {
    return _len;
}

void String::move(String& str){
    release();
    
    _data = str._data;
    _len = str._len;
    _cap = str._cap;
    
    str._data = nullptr;
    str._len = 0;
    str._cap = 0;
}

const char* String::c_str() const {
    return _data ? _data : "";
}

bool String::operator==(const char *s) const {
    return strcmp(c_str(), s) == 0;
}

bool String::operator==(const String &str) const {
    return operator==(str._data);
}

char String::operator[](size_t idx) const {
    if (idx >= _len) {
        throw std::runtime_error("idx out of range.\n");
    }
    return _data[idx];
}

void test_String(){
    String s("HELLO.");
    TEST(s == "HELLO.");
    String a = s;
    TEST(a == "HELLO.");
    TEST(a == s);
    String b = a + "World.";
    TEST(b == "HELLO.World.");
    TEST(a == "HELLO.");
    String c = a + b;
    a += b;
    dump_var(a);
    dump_var(c);
    TEST(a == c);
}
