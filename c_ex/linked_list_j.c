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
    Node* next;
};

typedef struct
{
    size_t len;
    Node *head;
} LinkedList;

Node* lls_has_node(LinkedList *lls, Node *target_node);
Node *lls_pop_head(LinkedList *lls);

void node_init(Node* node, int value)
{
    node->v = value;
    node->next = NULL;
}

Node* node_new(int value) {
    Node *node = (Node *)my_malloc(sizeof(Node));
    if (!node) return NULL;

    node_init(node, value);
    return node;
}

void node_release(Node *node)
{
    if (!node) return;
    assert(node->next == NULL);

    node->v = 0;
    node->next = NULL;
}

void node_free(Node* node) {
    if (!node) return;
    node_release(node);
    my_free(node);
}

void lls_init(LinkedList* lls)
{
    lls->len = 0;;
    lls->head = NULL;
}

void lls_release(LinkedList *lls)
{
    Node* p;
    while ((p = lls_pop_head(lls))) {
        node_free(p);
    }
}

Node *lls_tail(LinkedList *lls) {
    for (Node *p = lls->head ;p; p = p->next) {
        if (!p->next) return p;
    }
    return NULL;
}

void lls_sorted_insert(LinkedList *lls, Node *new_node) {
    Node* target = NULL;
    for (Node* p = lls->head; p ; p= p->next) {
        if (new_node->v <= p->v) break;
        target = p;
    }
    lls_insert_after(lls, target, new_node);
}

void lls_insert_after(LinkedList *lls, Node *target_node, Node *new_node)
{
    assert(new_node->next == NULL);

    if (target_node == NULL) {
        new_node->next = lls->head;
        lls->head = new_node;
    } else {
        assert(lls_has_node(lls, target_node) != NULL);
        new_node->next = target_node->next;
        target_node->next = new_node;
    }
    lls->len++;
    return;
}

void lls_insert(LinkedList *lls, Node *node) {
    lls_insert_after(lls, NULL, node);
}

void lls_append(LinkedList *lls, Node *node) {
    lls_insert_after(lls, lls_tail(lls), node);
}

Node* lls_insert_value(LinkedList *lls, int value) {
    Node* p = node_new(value);
    lls_insert(lls, p);
    return p;
}

Node *lls_find_node_by_value(LinkedList *lls, int v)
{
    Node *p = lls->head;
    while (p)
    {
        if (p->v == v) return p; // return the 1st occurence.
        p = p->next;
    }
    return NULL;
}

Node* lls_has_node(LinkedList *lls, Node *target_node)
{
    // if (*target_node== NULL) {

    // }
    for (Node *p = lls->head; p; p = p->next) {
        if (p == target_node) return p;
    }

    assert(0 && "no such node in linkedlist");
    return NULL;
}

Node *lls_find_previous(LinkedList *lls, Node *target_node)
{
    for (Node *p = lls->head; p; p = p->next)
    {
        if (p->next == target_node)
        {
            return p;
        }
    }
    return NULL; // if target_node is head: return NULL;
}

Node *lls_remove_node_with_prev(LinkedList *lls, Node *pv_node, Node *node)
{
    if (!node) return NULL;
    
    if (lls->head == node) {
        lls->head = node->next;
    } else {
        // Node* pv_node = lls_find_previous(lls, node);
        if (!pv_node) {
            puts("ERROR: pv_node is NULL");
            return NULL;
        }
        pv_node->next = node->next;
    }

    assert(lls->len > 0);
    lls->len--;
    node->next = NULL;
    return node;
}

Node *lls_remove_node(LinkedList *lls, Node *node)
{
    Node* pv_node = lls_find_previous(lls, node);
    return lls_remove_node_with_prev(lls, pv_node, node);
}

Node *lls_pop_head(LinkedList *lls)
{
    return lls_remove_node(lls, lls->head);
}

Node *lls_pop_tail(LinkedList *lls)
{
    Node* pv_node = NULL;
    
    for (Node*p = lls->head; p; p=p->next) {
        if(!p->next->next) {
            pv_node = p;
            break;
        }
    }
    Node* tail = pv_node->next;
    
    return lls_remove_node_with_prev(lls, pv_node, tail); 
}

Node *lls_remove_by_value(LinkedList *lls, int v)
{
    Node* node = lls_find_node_by_value(lls, v);
    if (!node) return NULL;
    return lls_remove_node(lls, node);
}

void lls_free_node(LinkedList *lls, Node *node)
{
    Node *p = lls_remove_node(lls, node);
    if (p) node_free(p);
}

void lls_print(LinkedList *lls)
{
    // printf("lls len: %zu\n", lls->len);
    for (Node *p = lls->head; p; p = p->next)
    {
        printf("[%i]->", p->v);
    }
    printf("| <len: %zu>\n", lls->len);
}

void lls_reverse(LinkedList *lls)
{
    LinkedList tmp = *lls;
    lls->head = NULL; 
    lls->len = 0;
    Node* p;
    while ((p = lls_pop_head(&tmp))) {
        lls_insert(lls, p);
    }
}



// ===============
int main()
{

    LinkedList list;
    LinkedList* lls = &list;
    lls_init(lls);
    Node* v0 = node_new(0);
    lls_append(lls, v0);
    Node* v1 = lls_insert_value(lls, 1);
    Node *v2 = node_new(2);
    Node *v3 = node_new(3);
    lls_insert_after(lls, v1, v2);
    lls_print(lls);
    TEST(lls_find_node_by_value(lls, 0) == v0);
    TEST(lls_find_node_by_value(lls, 8) == NULL);
    TEST(lls_find_previous(lls, v2) == v1);
    TEST(lls_find_previous(lls, v3) == NULL );
    node_free(v3);
    TEST(lls_pop_head(lls) == v1);
    node_free(v1);
    lls_print(lls);
    TEST(lls_pop_tail(lls) == v0);
    node_free(v0);
    lls_print(lls);
    TEST(lls_remove_by_value(lls, 5) == NULL);
    TEST(lls_remove_by_value(lls, 2) == v2);
    node_free(v2);
    lls_append(lls, node_new(1));
    lls_append(lls, node_new(2));
    lls_append(lls, node_new(3));
    lls_print(lls);
    lls_reverse(lls);
    lls_print(lls);
    lls_release(lls);
    TEST(n_malloc == 0);

    return 0;
}