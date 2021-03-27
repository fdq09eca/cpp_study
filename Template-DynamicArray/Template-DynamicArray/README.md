# Dynamic Array

## pre-do
1. watch [this](https://www.youtube.com/watch?v=h7Cpnf3gF84&t=6s)

## objective
- [  ] write an Dynamic array for `int` 
- [  ] use `Template` to write `DynamicArray`

## spec

- `void append(int v)`
- `void append(const DynamicArray& arr)`
- `sort()` selection sort implementation
- `int* search(int v)`  binary search implementation
- `void del(int idx)`
- `void reverse()`



## questions

1. how to have the function `arr.print()` such that it will automatically call `std::cout << arr;`?
2. if i have  `const int& operator[](const int idx) const`:
    how can i have the set value one, e.g. `arr[0] = 0`?
3. if i have `DynamicArray(const int* data, const int& len_)`:
    how can construct without assigning a `int arr[]`? e.g. `DynamicArray({1, 2, 3}, 3)`  

