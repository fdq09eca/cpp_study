# Dynamic Array

## pre-do
1. watch [this](https://www.youtube.com/watch?v=h7Cpnf3gF84&t=6s)

## objective

- [x] write an Dynamic array for `int` 
- [x] use `Template` to write `DynamicArray`
    - [x] `DynArray<int> intArr;`
    - [x] `DynArray<float> floatArr;`
    - [o] `DynArray<MyStruct> structArr;` 

## spec

- [x]  `void append(int v)`
- [x]  `void append(const DynamicArray& arr)`
- [x]  `sort()` selection sort implementation
- [x] `int* search(int v)`  binary search implementation
- [x] `void del(int idx)`
- [x] `void reverse()`

## questions

1. how to have the function `arr.print()` such that it will automatically call `std::cout << arr;`?
2. if i have  `const int& operator[](const int idx) const`:
    how can i have the set value one, e.g. `arr[0] = 0`?
3. if i have `DynamicArray(const int* data, const int& len_)`:
    how can construct without assigning a `int arr[]`? e.g. `DynamicArray({1, 2, 3}, 3)`  
4. why singleton can not have `DynamicArray` as member variable..?
5. what is qualifier in template? e.g.`template<typename {{ qulifier }}::{{ name }}>`

```c
template<class Y>
DynamicArray<Y> operator+(const DynamicArray<Y>& arr) const {
    return DynamicArray<Y>(*this).append(arr);
}
```

this work
```c
// case 1
DynamicArray<int> arr3 = arr + arr2;
DynamicArray<float> arr4 = arr_f + arr2_f;
```

this does not work
```c
// case 2
DynamicArray arr3 = arr + arr2;
DynamicArray arr4 = arr_f + arr2_f;
```

6. how can case 2 work?

### CPP video

1. virtual table init: how does the constructor matter to the virtual function update? 
    [see here.](https://youtu.be/b_hRxxQy2WQ?list=PLeGk08zVu4566pxRefXH0zr1FDL4BGUUG&t=1805)
2. how virtual table is rewritten by copying another class?
    [see here](https://youtu.be/b_hRxxQy2WQ?list=PLeGk08zVu4566pxRefXH0zr1FDL4BGUUG&t=2567)
