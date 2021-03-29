#include "Array.h"
#include "MyString.h"
#include "UniquePtr.h"

#include <vector>

void test_IntArray() {
	Array<int> a;	
	for (int i = 0; i < 5; i++) {
		a.append(i);
	}

	DUMP_VAR(a);

	{
		size_t idx;
		bool found = a.find(idx, 10);
		DUMP_VAR(found);
		if (found) {
			DUMP_VAR(idx);
		}
	}
}

void test_MyStringArray() {
#if 0
	MyString s1;
	s1 = "hello";

//	MyString s2(s1);
//	MyString s2 = s1; // same as MyString s2(s1)

	MyString s2;
//	s2 = s1; // copy

//	s2.move(s1);
	s2 = std::move(s1); // s1 -> s1&&

//	s2.func(std::move(s1));

	DUMP_VAR(s1);
	DUMP_VAR(s2);
#endif

#if 1
	Array<MyString> a;

	MyString tmp = "hi";

	for (int i = 0; i < 2; i++) {
//		a.append("A");
		a.emplace_back( std::move(tmp) );
	}

	DUMP_VAR(a);
	DUMP_VAR(MyString::s_count);
#endif

	//{
	//	size_t idx;
	//	bool found = a.find(idx, 10);
	//	DUMP_VAR(found);
	//	if (found) {
	//		DUMP_VAR(idx);
	//	}
	//}
}

void func(int a) {
	throw std::exception("");
}

void func_no(int a) noexcept {
}

void caller() {
	if (noexcept(func(1))) {
		std::cout << "a";
	} else {
		std::cout << "b";
	}
}

template<class T>
UniquePtr<T> make_unique(T* p) {
	return UniquePtr<T>(p);
}

void test_UniquePtr() {
	class MyData : public NonCopyable {
	public:
		int i = 0;
	};

	auto* raw = new MyData();

//	auto u = UniquePtr<MyData>(raw);
	auto u = make_unique(raw);

//	u.assign(new MyData);

//	u.get()->i = 10;
	u->i = 10;

	using MyDataPtr = UniquePtr<MyData>;

	Array<MyDataPtr> arr;

	arr.resize(4);
}

class Data : public NonCopyable {
public:
	Data() = default;

	int a = 1;
	float b = 0;
};

template<>
class std::is_trivially_copyable<Data> {
public:
	const static bool value = true;
};

int main()
{
//	std::vector<Data> v;
//	v.resize(10);

//	caller();

	test_IntArray();
//	test_MyStringArray();
//	test_UniquePtr();
}
