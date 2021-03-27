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
    DynamicArray arr;
    DynamicArray arr2;

private:
    void print_stage() {
        dump_var(arr);
        dump_var(arr2);
    }

    void test_name(const char* name) {
        std::cout << "\n== TEST::" << name << " ==\n";
        restart();
        print_stage();
    }
    
    void init_arr() { // odd arr
        arr.clean();
        for (int    i = 1,  idx = 0;
                    i < 10;
                    i += 2, idx++) {
            arr.append(i);
        }
    }
    
    void init_arr2(){ // even arr
        arr2.clean();
        for (int    i = 0,  idx = 0;
                    i < 10;
                    i += 2, idx++) {
            arr2.append(i);
        }
    }
    
    void reset() {
        arr.clean();
        arr2.clean();
    }
    
    void restart() {
        reset();
        init_arr();
        init_arr2();
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
    
    void find_min() {
        test_name("find_min()");
        int min_v = *arr.local_min(0, arr.last_idx());
        dump_var(min_v);
        TEST( min_v == 1);
    }
    
    void sort() {
        test_name("sort()");
        arr.append(arr2).sort();
        print_stage();
        int ans_[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        DynamicArray ans(ans_, 10);
        dump_var(ans);
        TEST(arr == ans);
        dump_var(arr);
    }
    
    void search(){
        test_name("search()");
        int arr_len = arr.get_len();
        for (int i = 1, idx = 0; idx < arr_len; i+=2, idx++) {
            const int* v = arr.search(i);
            const int* u = arr2.search(i - 1);
            TEST(*v == arr[idx]);
            TEST(*u == arr2[idx]);
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
            const int len_before_del = arr.get_len();
            dump_var(arr);
            dump_var(i);
            dump_var(arr.del(i));
            TEST(arr.search(i) == nullptr);
            TEST(arr.get_len() == len_before_del - 1);
        }
    }
    
    void insert_before(){
        test_name("insert()");
        arr.insert_before(1, 0);
        dump_var(arr);
    }
    
    void operator_equal() {
        test_name("optor_eq() - test =");
        DynamicArray a(arr);
        
        dump_var(a);
        
//        arr = arr2;
//        std::cout << "after `arr = arr2;`\n";
//        print_stage();
//        for (int    idx = 0, arr2_len = arr2.get_len();
//                    idx < arr2_len;
//                    idx ++) {
//            TEST(arr[idx] == arr2[idx]);
//        }
    }
    
    void operator_plus() {
        test_name("operator_plus()");
        DynamicArray arr3 = arr + arr2;
        dump_var(arr3);
        print_stage();
        TEST(arr3 == arr.append(arr2));
    }
    
    
    
    void run() {
//        append_int();
//        append_DynamicArray();
//        operator_equal();
//        get_len();
//        find_min();
//        sort();
//        search();
//        del();
//        insert_before();
        operator_plus();
    }
    
};

#endif /* Test_hpp */
