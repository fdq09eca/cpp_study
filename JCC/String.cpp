#include <stdio.h>
#include <string.h>
#include <iostream>

#define TEST(EXPR)                                                                  \
    do                                                                              \
    {                                                                               \
        printf("[%s] Line %3d: %s\n", ((EXPR) ? " OK " : "FAIL"), __LINE__, #EXPR); \
    } while (0) //-------------------

#define dump_var(X)               \
    do                            \
    {                             \
        std::cout << #X " " << X; \
    } while (false)
//=====

const size_t next_pow_of_two(size_t &v)
{
    size_t i = 1;
    while (i < v)
    {
        i *= 2;
    }
    return i;
}

class String
{
private:
    size_t _len;
    size_t _cap;
    char *_data;

public:
    String() : _len(0), _cap(0), _data(nullptr) {} //default type constructor

    String(const char *s) : _len(0), _cap(0), _data(nullptr)
    {
        append(s);
    }

    String(const String &str) : _len(0), _cap(0), _data(nullptr)
    {
        append(str._data);
    }

    void operator=(const String &s)
    {
        clear();
        append(s._data);
    }

    void operator=(const char *s)
    {
        clear();
        append(s);
    }

    ~String()
    {
        clear();
        delete[] _data;
        _data = nullptr;
    }

    void clear()
    {
        resize(0);
    }

    String operator+(const char *s) const{
        String new_str(_data);
        return new_str.append(s);
    }

    String &append(const char *s)
    {
        if (!s) return *this;
        size_t old_len = _len;
        size_t s_len = strlen(s);
        size_t new_len = _len + s_len;
        resize(new_len);
        memcpy(_data + old_len, s, s_len * sizeof(char)); //<<
        _data[new_len] = 0;
        return *this;
    }
    
    void operator+=(const char *s){
        append(s);
    }
    
    String &append(const String& s){
        return append(s._data);
    }

    void operator+=(const String& s){
        append(s);
    }
    

    void resize(size_t new_len)
    {
        if (new_len > _cap)
        {
            size_t new_cap = next_pow_of_two(new_len);
            char *new_data = new char[new_cap + 1];
            memcpy(new_data, _data, _len * sizeof(char));
            delete[] _data;
            _data = new_data;
            _cap = new_cap;
        }
        _len = new_len;
        if (_data)
            _data[_len] = 0;
    }

    const char *c_str() const
    {

        return _data ? _data : "";
    }

    bool operator==(const char *s)
    {
        return strcmp(s, c_str()) == 0;
    }
};

std::ostream &operator<<(std::ostream &s, String &str)
{
    s << str.c_str();
    return s;
}

int main()
{
    String s("HELLO!");
    TEST(s == "HELLO!");
    s = "";
    TEST(s == "");
    String a; 
    TEST(a == "");
    s.append("OK");
    TEST(s == "OK");
    s.append("OK").append("OK");
    TEST(s == "OKOKOK");
    a = s + "Noooooo";
    TEST(s == "OKOKOK");
    TEST(a == "OKOKOKNoooooo");
    s+=s;
    TEST(s == "OKOKOKOKOKOK");


    // std::cout << a << "\n";
    // s.append("World!");
    // std::cout << s << "\n";
    // String a = s.concat("YO?");
    // std::cout << a << "\n";
    // std::cout << s << "\n";
}