#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define TEST(EXPR) \
    do { \
        printf("[%s] Line %3d: %s\n", ((EXPR) ? " OK " : "FAIL"), __LINE__, #EXPR); \
    } while(0) \
//-------------------
size_t n_malloc = 0;

void* my_malloc(size_t n){
    n_malloc ++;
    return malloc(n);
}

void my_free(void* p) {
    n_malloc--;
    free(p);
}

//== Node ==
struct _Node;
typedef struct _Node Node;

struct _Node
{
    int v;
    Node* prev;
    Node* next;
};

typedef struct
{
    size_t len;
    Node *head;
    Node *tail;
} LinkedList;


int main() {
    return 0;
}