#pragma once

#include "Common.h"


class MyString : public NonCopyable {
public:
	static size_t s_count;
	MyString() {
		s_count++;
	}

#if 1 // non-copyable
	//MyString(const MyString&) = delete;
	//void operator=(const MyString& r) = delete;

#else
	MyString(const MyString& r) {
//		std::cout << "MyString(const MyString& r)\n";
		set(r.c_str());
	}

	void operator=(const MyString& r) {
//		std::cout << "operator=(const MyString& r)\n";
		set(r.c_str());
	}
#endif

	//void move(MyString& r) {
	//	clear();
	//	_data = r._data;
	//	r._data = nullptr;
	//}

	MyString(MyString && r) {
		operator=(std::move(r));
	}

	void operator=(MyString && r) noexcept { // move semantics
		clear();
		_data = r._data;
		r._data = nullptr;
	}

	MyString(const char* sz) {
//		std::cout << "MyString(const char* sz)\n";
		s_count++;
		set(sz);
	}

	~MyString() {
		clear();
	}

	void set(const char* sz) {
		clear();
		size_t n = strlen(sz);
		_data = reinterpret_cast<char*>(malloc(n + 1));
		std::cout << "malloc\n";

		strcpy(_data, sz);
	}


	void operator=(const char* sz) {
		set(sz);
	}

	void clear() {
		if (_data) {
			free(_data);
			_data = nullptr;
		}
	}

	bool operator==(const MyString& r) const {
		return strcmp(_data, r._data) == 0;
	}

	const char* c_str() const { return _data ? _data : ""; }

private:
	char* _data = nullptr;
};

inline
std::ostream& operator<<(std::ostream& s, const MyString& v) {
	s << v.c_str();
	return s;
}