#pragma once

#include "Common.h"

class File {
public:
	File(File && r) noexcept {
		_f = r._f;
		r._f = nullptr;
	}

	~File() {
		close();
	}

	void open(const char* filename) {
		_f = fopen(filename, "rb");
	}

	void close() {
		if (_f) {
			fclose(_f);
		}
	}

private:
	FILE* _f = nullptr;
};
