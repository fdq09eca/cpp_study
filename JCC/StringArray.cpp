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

size_t next_pow_of_two(size_t v)
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
    String() : _len(0), _cap(0), _data(nullptr){};
    String(const char *s) : _len(0), _cap(0), _data(nullptr)
    {
        append(s);
    };

    String(const String &str) : _len(0), _cap(0), _data(nullptr)
    {
        *this = str;
    }

    ~String()
    {
        delete[] _data;
        _data = nullptr;
        clear();
        _cap = 0;
    }

    void clear()
    {
        resize(0);
    }

    void operator=(const String &str)
    {
        clear();
        append(str);
    }

    void reserve(size_t request_len)
    {
        if (request_len < _cap)
            return;
        size_t new_cap = next_pow_of_two(request_len);
        char *new_data = new char[new_cap + 1];
        memcpy(new_data, _data, _len * sizeof(char));
        delete[] _data;
        _data = new_data;
        _cap = new_cap;
    }

    void resize(size_t new_len)
    {
        reserve(new_len);
        _len = new_len;
    }

    String &append(const char *s)
    {
        if (s == nullptr)
            return *this;
        size_t s_len = strlen(s);
        size_t old_len = _len;
        size_t new_len = s_len + _len;
        resize(new_len);
        memcpy(_data + old_len, s, s_len * sizeof(char));
        _data[new_len] = 0;
        return *this;
    }

    String &append(const String &str)
    {
        return append(str._data);
    }

    void operator+=(const char *s)
    {
        append(s);
    }

    void operator+=(const String &str)
    {
        append(str);
    }

    const String operator+(const char *s) const
    {
        return String(*this).append(s);
    }

    const String operator+(const String &str) const
    {
        return String(*this).append(str);
    }

    const size_t len()
    {
        return _len;
    }

    const char *c_str() const
    {
        return _data ? _data : "";
    }

    bool operator==(const char *s) const
    {
        return strcmp(_data, s) == 0;
    }

    bool operator==(const String &str) const
    {
        return operator==(str._data);
    }

    char operator[](size_t idx) const
    {
        if (idx >= _len)
        {
            throw std::runtime_error("idx out of range.\n");
        }
        return _data[idx];
    }

    
};

std::ostream &operator<<(std::ostream &s, String &str)
{
    s << str.c_str();
    return s;
}

class StringArray
{
};

int main()
{
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

    // std::cout << s.append("WORLD!");
    return 0;
}