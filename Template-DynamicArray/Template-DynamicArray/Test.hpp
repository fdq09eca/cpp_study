//
//  Test.hpp
//  Template-DynamicArray
//
//  Created by ChrisLam on 27/03/2021.
//

#ifndef Test_hpp
#define Test_hpp

#include <stdio.h>
#include "DynamicArray.hpp"
#define TEST(EXPR)                                                                  \
    do                                                                              \
    {                                                                               \
        printf("[%s] Line %3d: %s\n", ((EXPR) ? " OK " : "FAIL"), __LINE__, #EXPR); \
    } while (0) //-------------------

#define dump_var(X)                        \
    do                                     \
    {                                      \
        std::cout << #X ": " << X << "\n"; \
    } while (false)

class Test{
    DynamicArray<int> arr;
    DynamicArray<int> arr2;
    DynamicArray<float> arr_f;
    DynamicArray<float> arr2_f;

private:
    
    void print_stage() {
        dump_var(arr);
        dump_var(arr2);
        dump_var(arr_f);
        dump_var(arr2_f);
    }
    

    void test_name(const char* name) {
        std::cout << "\n== TEST::" << name << " ==\n";
        restart();
        print_stage();
    }
    
    void init_arr() { // odd arr
        arr.clean();
        for (int i = 1,  idx = 0; i < 10; i += 2, idx ++) {
            arr.append(i);
        }
    }
    
    void init_arr2(){ // even arr
        arr2.clean();
        for (int i = 0,  idx = 0; i < 10; i += 2, idx ++) {
            arr2.append(i);
        }
    }
    
    void init_arr_f(){
        init_arr();
        for (int i = 0, arr_len = arr.get_len(); i < arr_len; i++) {
            arr_f.append(arr[i]/10.0f);
        }
    }
    
    void init_arr2_f(){
        init_arr2();
        for (int i = 0, arr2_len = arr2.get_len(); i < arr2_len; i++) {
            arr2_f.append(arr2[i]/10.0f);
        }
    }
    
    void reset() {
        arr.clean();
        arr2.clean();
        arr_f.clean();
        arr2_f.clean();
    }
    
    void restart() {
        reset();
        init_arr();
        init_arr2();
        init_arr_f();
        init_arr2_f();
    }

public:
    Test() {
        reset();
        init_arr();
        init_arr2();
    }
    
    void append_int() {
        // ===============
        test_name("append_int() - even int");
        for (int    i = 0, idx = 0;
                    i < 10;
                    i += 2, idx++) {
            arr2.append(i);
            TEST(arr2[idx] == i);
        }
        // ===============
        test_name("append_int() - odd int");
        for (int    i = 1,  idx = 0;
                    i < 10;
                    i += 2, idx++) {
            TEST(arr[idx] == i);
        }
    }
    
    void append_DynamicArray() {
        test_name("append_DynamicArray() - append arr without data");
        arr.clean();
        arr.append(arr2);
        for (int    i = 0,  idx = 0;
                    i < 10;
                    i += 2, idx ++) {
            TEST(arr[idx] == i);
        };
        TEST(arr.get_len() == 5);
        
        // ============
        test_name("append_DynamicArray() - check copy");
        arr.clean();
        arr.append(arr2);
        arr2.clean();
        for (int    i = 0,  idx = 0;
                    i < 10;
                    i += 2, idx++) {
            TEST(arr[idx] == i);
        };
        TEST(arr.get_len() == 5);
        
        // ==============
        test_name("append_DynamicArray() - append arr with data");
        int prev_last_idx = arr.last_idx();
        int prev_len = arr.get_len();
        
        arr.append(arr2);
        
        int curr_last_idx = arr.last_idx();
        int append_len = arr2.get_len();
        int curr_len = arr.get_len();
        
        for (int i = 0, idx = prev_last_idx + 1;
                 idx < curr_last_idx;
                 i += 2, idx ++) {
            TEST(arr[idx] == i);
        }
        TEST(curr_len == append_len + prev_len);
    }
    
   
    void get_len() {
        test_name("get_len()");
        TEST(arr.get_len() == 5);
        TEST(arr2.get_len() == 5);
    }
    
    
    void operator_bool_equal() {
        test_name("Template - int: int_operator_bool_equal()");
        TEST(arr == arr);
        TEST(arr2 == arr2);
        TEST(arr != arr2);
        TEST(arr2 != arr);
        
        test_name("Template - float: operator_bool_equal()");
        TEST(arr_f != arr2_f);
        TEST(arr2_f != arr_f);
        TEST(arr_f == arr_f);
        TEST(arr2_f == arr2_f);
    }
    
    
    void find_min() {
        test_name("find_min()");
        int min_v_int = *arr.local_min(0, arr.last_idx());
        float min_v_float = *arr_f.local_min(0, arr_f.last_idx());
        dump_var(min_v_int);
        dump_var(min_v_float);
        TEST( min_v_int == 1);
        TEST( float_eq(min_v_float, 0.1));
        
    }

    void sort() {
        test_name("sort()");
        
        arr.append(arr2);
        arr_f.append(arr2_f);
        print_stage();
        
        arr.sort();
        arr_f.sort();
        print_stage();
        
        int ans_int[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        float ans_float[] = {0, 0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f, 0.7f, 0.8f, 0.9f};
        DynamicArray<int> ans_i(ans_int, 10);
        DynamicArray<float> ans_f(ans_float, 10);
        
        dump_var(ans_i);
        dump_var(ans_f);
        
        TEST(arr == ans_i);
        TEST(arr_f == ans_f);

    }

    void search(){
        test_name("search()");
        int arr_len = arr.get_len();
        for (int i = 1, idx = 0; idx < arr_len; i+=2, idx++) {
            const int* v = arr.search(i);
            const int* u = arr2.search(i - 1);
            const float p = *v / 10.0f;
            const float q = *u / 10.0f;
            TEST(*v == arr[idx]);
            TEST(*u == arr2[idx]);
            TEST(p == arr_f[idx]);
            TEST(q == arr2_f[idx]);
        }

        arr.append(arr2).sort();
        dump_var(arr);
        for (int i = 0; i < arr.get_len(); i++) {
            const int* y = arr.search(i);
            TEST(*y == arr[i]);
        }
    }

    void del(){
        test_name("del()");

        for (int i = 1; i < 10; i += 2) {
            const int len_before_del_int = arr.get_len();
            const int len_before_del_float = arr_f.get_len();
            
            dump_var(arr);
            dump_var(i);
            dump_var(arr.del(i));
            TEST(arr.search(i) == nullptr);
            TEST(arr.get_len() == len_before_del_int - 1);
            
            float j = i / 10.0f;
            dump_var(arr_f);
            dump_var(j);
            dump_var(arr_f.del(j));
            
            TEST(arr_f.search(i) == nullptr);
            TEST(arr_f.get_len() == len_before_del_float - 1);
        }
    }
    

    void insert_at(){
        test_name("insert()");
        arr.insert_at(1, 0);
        arr_f.insert_at(1, 0.13579);
        dump_var(arr);
        dump_var(arr_f);
    }

    void operator_equal() {
        test_name("operator_equal()");
        DynamicArray<int> a(arr);
        DynamicArray<float> b(arr_f);
        dump_var(a);
        dump_var(b);
        for (int    idx = 0, arr2_len = arr2.get_len();
                    idx < arr2_len;
                    idx ++) {
            TEST(a[idx] == arr[idx]);
            TEST(b[idx] == arr_f[idx]);
        }

        arr = arr2;
        std::cout << "after `arr = arr2;`\n";
        print_stage();
        for (int    idx = 0, arr2_len = arr2.get_len();
                    idx < arr2_len;
                    idx ++) {
            TEST(arr[idx] == arr2[idx]);
            TEST(arr[idx] == arr2[idx]);
        }
    }

    void operator_plus() {
        test_name("operator_plus()");;
        DynamicArray<int> arr3 = arr + arr2;
        DynamicArray<float> arr4 = arr_f + arr2_f;
        dump_var(arr3);
        dump_var(arr4);
        TEST(arr3 == arr.append(arr2));
        TEST(arr4 == arr_f.append(arr2_f));
    }
    
    
    
    void run() {
        append_int();
        append_DynamicArray();
        operator_bool_equal();
        get_len();
        find_min();
        sort();
        search();
        del();
        insert_at();
        operator_equal();
        operator_plus();
    }
    
};

#endif /* Test_hpp */
