#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <time.h>

#define TEST(EXPR) \
    do { \
        printf("[%s] Line %3d: %s\n", ((EXPR) ? " OK " : "FAIL"), __LINE__, #EXPR); \
    } while(0) \
//========

size_t g_malloc_count = 0;

void* my_malloc(size_t n){
    g_malloc_count ++;
    return malloc(n);
}

void my_free(void* p) {
    g_malloc_count--;
    free(p);
}

//=========

#if _DEBUG
  #define debug_print(...)  printf(__VA_ARGS__)
#else
  #define debug_print(...)
#endif

#define STEP_SIZE 10 // 0: if STEP_SIZE 0 -> pow of 2
// == ArrayList ==

typedef struct {
    int* data;
    size_t cap;
    size_t size;
} ArrayList;


void ArrayList_init(ArrayList* als) {
    als->data = NULL;
    als->size = 0;
    als->cap = 0;
}

void ArrayList_release(ArrayList* als) {
    if (als->data) {
        free(als->data);
    }
    als->size = 0;
}

void ArrayList_free(ArrayList* als) {
    ArrayList_release(als);
    my_free(als);
}

ArrayList* ArrayList_new() {
    ArrayList* als = my_malloc(sizeof(ArrayList));
    ArrayList_init(als);
    return als;
}

size_t next_pow_of_two(size_t v) {
    #if 0 
        size_t i = 1;
        while (i < v) {
            i *= 2;
        }
        return i;
    #else 
        assert(sizeof(v) == 8); // 8 byte -> x64
        v--; // https://graphics.stanford.edu/~seander/bithacks.html#RoundUpPowerOf2
        v |= v >> 1; 
        v |= v >> 2;  
        v |= v >> 4; 
        v |= v >> 8;
        v |= v >> 16;
        v |= v >> 32; // 64/2
        v++; 
        return v;
    #endif
}

void ArrayList_reserve(ArrayList* als, size_t reserve_size) {
    if (reserve_size <= als->cap) {
        return;
    }

#if (STEP_SIZE == 0) 
    size_t new_cap = next_pow_of_two(reserve_size);
#else
    size_t new_cap = (reserve_size + STEP_SIZE - 1) / STEP_SIZE * STEP_SIZE; //closest int of multiple of x
#endif

    int* new_data = (int*) my_malloc(sizeof(int) * new_cap);
    
    if (!new_data) {
        debug_print("new_data malloc fail\n")
        return;
    }
    
    // {   // memcpy
    //     int* src = als->data;
    //     int* end = src + als->size;
    //     int* dst = new_data;

    //     for (;src < end ;src++, dst++) {
    //         *dst = *src;
    //     } 
    // }
    memcpy(new_data, als->data, sizeof(int)*als->size);


    my_free(als->data);
    als->data = new_data;
    als->cap = new_cap;
}

void ArrayList_resize(ArrayList* als, size_t new_size) {
    ArrayList_reserve(als, new_size);
    als->size = new_size;
}

void ArrayList_insert(ArrayList* als, size_t idx, int v) {
    if (idx > als->size){
        debug_print("ERROR: idx > size");
        return;
    }
    ArrayList_resize(als, als->size + 1);
    int* src = als->data + idx;
    size_t remain_elemnts = als->size - idx;
    memmove(src+ 1, src, sizeof(int) * remain_elemnts);
    als->data[idx] = v;
}

void ArrayList_delete(ArrayList* als, size_t idx){
    if (idx > als->size ) {
        debug_print("ERROR: idx > size");
        return;
    }
    int* src = als->data + idx;
    size_t remain_elements = als->size - idx;
    memmove(src, src+1, remain_elements);
    ArrayList_resize(als, als->size - 1);  
}

void ArrayList_reverse(ArrayList* als) {
    size_t n = als->size/2;
    
    for (size_t i = 0; i < n; i++ ) {
        int* a = &als->data[i];
        int* b = &als->data[als->size - i - 1];
        int tmp = *a;
        *a = *b;
        *b = tmp;
    }
}

int* ArrayList_find(ArrayList* als, int value){
    int* p = als->data;
    int* end = p + als->size;
    for (; p < end; p++) {
        if (*p == value) return p;
    }
    return NULL;
}

int* ArrayList_binary_search(ArrayList* als, int value){
    // lazy evaluation
    if (als->size <= 0) {
        return NULL;
    }
    
    size_t start = 0; 
    size_t end = als->size;
    size_t m;
    while (start < end) {
        m = (start + end) / 2;
        size_t v = als->data[m];
        if (v > value) {
            end = m; 
            continue;
        }
        if (v < value) {
            start = m + 1;
            continue;
        }
        return &(als->data[m]);
    }
    return NULL;
}

int* ArrayList_find_min(ArrayList* als, size_t from_idx) {
    if (als->size <= from_idx) {
        return NULL;
    }
#if 0
    int min = als->data[from_idx];
    size_t min_idx = from_idx;
    for (size_t i = from_idx + 1 ; i < als->size; i++) {
        if (als->data[i] < min) {
            min = als->data[i];
            min_idx = i;
        }
    }
    return &als->data[min_idx];
#else
    int* p = als->data + from_idx;
    int* end = als->data + als->size;
    int* min_p = p;
    int min = *p;
    p++;
    for (; p < end; p++) {
        if (*p < min) {
            min = *p;
            min_p = p;
        }
    }
    return min_p;
#endif
    
}

void ArrayList_selection_sort(ArrayList* als) {
    int* p = als->data;
    int* end = p + als->size;
    size_t from = 0;
    for (; p < end; p++, from++) {
        int* target = ArrayList_find_min(als, from);
        if (target== p) continue;
        int tmp = *target;
        *target = *p;
        *p = tmp;
    }
}


void ArrayList_append(ArrayList* als, int v) {
    size_t i = als->size;
    ArrayList_resize(als, i + 1);
    als->data[i] = v;
}

void ArrayList_print(ArrayList* als) {
    for (size_t i = 0; i < als->size; i ++) {
        printf("%i ", als->data[i]);
    }
    printf("\n");
}


int main(){
    srand(time(NULL));
    ArrayList l;
    ArrayList *als = &l;
    ArrayList_init(als);
    for (int i = 11; i >= 0; i--) {
        // ArrayList_append(als, rand() % 10);
        ArrayList_append(als, i);
    }
    ArrayList_print(als);

    ArrayList_selection_sort(als);
    ArrayList_print(als);
    
    for (int i = 11; i >= 0; i--) {
        TEST(*(ArrayList_binary_search(als, i)) == i);
    }
    for (int i = 15; i >= 12; i--) {
        TEST(ArrayList_binary_search(als, i) == NULL);
    }
    
    for (int i = 11; i >= 0; i--) {
        ArrayList_delete(als,0);
        TEST(als->size == i);
    }
    TEST(als->size == 0);
    ArrayList_release(als);
    TEST(g_malloc_count == 0);
    return 0;
}