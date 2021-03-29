#pragma once

#include "Common.h"

template<class T>
class UniquePtr : public NonCopyable {
public:
	UniquePtr() = default;

	UniquePtr(T* p) : _p(p) {
	}

	UniquePtr(UniquePtr && r) noexcept {
		operator=(std::move(r));
	}

	void operator=(UniquePtr && r) noexcept {
		assign(r._p);
		r._p = nullptr;
	}

	~UniquePtr() {
		assign(nullptr);
	}

	void assign(T* p) noexcept {
		if (_p) {
			delete _p;
		}
		_p = p;
	}

	      T* get()       { return _p; }
	const T* get() const { return _p; }

	T* operator->() { return _p; }

private:
	T* _p = nullptr;
};
