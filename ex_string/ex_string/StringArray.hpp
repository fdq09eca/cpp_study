//
//  StringArray.hpp
//  ex_string
//
//  Created by ChrisLam on 12/02/2021.
//

#ifndef StringArray_hpp
#define StringArray_hpp
#include "MyString.hpp"

class StringArray{
private:
    size_t _len;
    size_t _cap;
    String* _data;
public:
    StringArray(): _len(0), _cap(0), _data(nullptr){};
    StringArray(const StringArray&);
    ~StringArray();
    
    inline size_t len() const { return _len; };
    void append(const String& str);
    void append(const char* s); // no String tmp construct.
    void append_move(String& str);
    void reserve(size_t request_len);
    void resize(size_t new_len);
    
    void operator=(const StringArray& arr);
    inline const String& operator[](size_t idx) const {
        assert(idx < _len);
        return _data[idx];
    }
};

inline std::ostream& operator<<(std::ostream& s, const StringArray& arr){
    s << "[";
    for (size_t i = 0; i < arr.len(); i ++) {
        if (i > 0) {
            s << ", ";
        }
        s << arr[i];
    }
    s << "]";
    return s;
}

void test_StringArray();
#endif /* StringArray_hpp */
