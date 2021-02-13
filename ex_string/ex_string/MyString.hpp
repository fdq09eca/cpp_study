#ifndef MyString_hpp
#define MyString_hpp

#include <stdio.h>
#include <iostream>
#include <string>

#define TEST(EXPR)                                                                  \
do                                                                              \
{                                                                               \
printf("[%s] Line %3d: %s\n", ((EXPR) ? " OK " : "FAIL"), __LINE__, #EXPR); \
} while (0) //-------------------

#define dump_var(X)                                     \
do                                                  \
{                                                   \
std::cout << "dump_var: " #X ": " << X << "\n"; \
} while (false)
//=====

size_t next_pow_of_two(size_t v);
class String
{
private:
    size_t _len;
    size_t _cap;
    char *_data;
    
public:
    String();
    String(const char *s);
    String(const String &str);
    
    ~String();
    
    void clear();
    void release();
    
    void reserve(size_t request_len);
    void resize(size_t new_len);
    void move(String& str);
    
    String &append(const char *s);
    String &append(const String &str);
    
    void operator=(const String &str);
    void operator+=(const char *s);
    void operator+=(const String &str);
    bool operator==(const char *s) const;
    bool operator==(const String &str) const;
    char operator[](size_t idx) const;
    
    String operator+(const char *s) const;
    String operator+(const String &str) const;
    
    size_t len() const;
    const char *c_str() const;
    
    
    
};

inline std::ostream &operator<<(std::ostream &s, const String &str){
    s << str.c_str();
    return s;
    
}
#endif /* MyString_hpp */
