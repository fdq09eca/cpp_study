#pragma once

#include "Common.h"

template<class T>
class is_memcpy_able { // std::is_trivially_copyable
public:
	const static bool value = false;
};

template<>
class is_memcpy_able<int> {
public:
	const static bool value = true;
};

template<class T>
class Array {
public:
	~Array() { release(); }
	void clear() { resize(0); }
	
	void release();
	void append(const T& v);

	template<class... ARGS>
	void emplace_back(ARGS &&... args);

	void resize(size_t n);
	void reserve(size_t n);
	bool find(size_t& outIndex, const T& v);

	size_t size() const { return _size; }

	const T& operator[](size_t i) const { return _data[i]; }

private:
	T* _data = nullptr;
	size_t _size = 0;
	size_t _cap = 0;
};

template<class T> inline
void Array<T>::release() {
	clear();
	if (_data) {
		free(_data);
		_data = nullptr;
	}
}

template<class T>
template<class... ARGS> inline
void Array<T>::emplace_back(ARGS &&... args) {
	resize(_size + 1);
	T* p = &_data[_size - 1];
	new (p) T(std::forward<ARGS>(args)... );
}

template<class T> inline
void Array<T>::append(const T& v) {
	resize(_size + 1);
	T* p = &_data[_size - 1];
	//new (p) T(); // ctor
	//*p = v; // copy
	new (p) T(v); // copy ctor
} 

template<class T> inline
void Array<T>::resize(size_t newSize) {
	reserve(newSize);

	if (std::is_trivially_copyable<T>::value) {
		for (size_t i = newSize; i < _size; i++) {
			_data[i].~T();
		}
	}
	_size = newSize;
}

template<class T> inline
void Array<T>::reserve(size_t n) {
	if (n <= _cap) return;
	size_t newCap = next_pow_of_two(n);
	T* newData = reinterpret_cast<T*>(malloc(sizeof(T) * newCap));

	try {
		if (std::is_trivially_copyable<T>::value) { // memcpy-able 
			memcpy(newData, _data, _size * sizeof(T));
		} else {
			for (size_t i = 0; i < _size; i++) {
				T& src = _data[i];
				T& dst = newData[i];
				new(&dst) T(std::move(src)); // move  ctor, placement new
				src.~T(); // dtor
			}
		}

	} catch (std::exception) {
		if (_data) {
			free(_data);
		}
		throw;
	}

	if (_data) {
		free(_data);
	}

	_data = newData;
	_cap = newCap;
}

template<class T> inline
bool Array<T>::find(size_t& outIndex, const T& v) {
	for (size_t i = 0; i < _size; i++) {
		if (_data[i] == v) {
			outIndex = i;
			return true;
		}
	}
	return false;
}

template<class T> inline
std::ostream& operator<<(std::ostream& s, const Array<T>& v) {
	s << '[';
	for (size_t i = 0; i < v.size(); i++) {
		if (i > 0) s << ", ";
		s << v[i];
	}
	s << ']';
	return s;
}
