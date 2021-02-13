#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

//== Node ==
struct _Node;
typedef struct _Node Node;
struct _Node
{
    int v;
    Node *next;
};
// typedef struct Node
// {
//     int v;
//     struct Node *next;
// } Node;

Node *node_init(int value)
{
    Node *node = (Node *)malloc(sizeof(Node));
    if (!node)
        return NULL;
    // assert(node);
    node->v = value;
    node->next = NULL;
    return node;
}

void node_release(Node *node)
{
    assert(node);
    if (!node)
        return;
    node->v = 0;
    assert(node->next == NULL);
    node->next = NULL;
    free(node);
}

//== LinkedList ==
typedef struct
{
    size_t len;
    Node *head;
} LinkedList;

LinkedList *lls_init(int v)
{
    LinkedList *lls = (LinkedList *)malloc(sizeof(LinkedList));
    lls->head = node_init(v);
    lls->len++;
    return lls;
}

void lls_release(LinkedList *lls)
{
    lls->len = 0;

    Node *p = lls->head;
    Node *next; // tmp pointer
    while (p)   // free all node.
    {
        next = p->next;
        p->next = NULL;
        node_release(p);
        p = next;
    }
    free(lls);
    return;
}

Node *lls_tail(LinkedList *lls)
{
    Node *p = lls->head;
    while (p)
    {
        if (!p->next)
        {
            return p;
        }
        p = p->next;
    }
    return p;
}

void lls_push(LinkedList *lls, Node *node)
{
    Node *p = lls->head;
    node->next = p;
    lls->head = node;
    lls->len++;
    return;
}

void lls_append(LinkedList *lls, Node *node)
{
    if (!lls->head)
    {
        lls->head = node;
    }
    else
    {
        lls_tail(lls)->next = node;
    }
    lls->len++;
    return;
}

void lls_append_as_tail(LinkedList *lls, Node *node)
{
    node->next = NULL;
    lls_append(lls, node);
}

Node *lls_find_value(LinkedList *lls, int v)
{
    Node *p = lls->head;
    while (p)
    {
        if (p->v == v)
        {
            break; // return the 1st occurence.
        }
        p = p->next;
    }
    return p; // return NULL if not found
}

Node *lls_find_node(LinkedList *lls, Node *t_node)
{

    for (Node *p = lls->head; p; p = p->next)
    {
        if (p == t_node)
        {
            return p;
        }
    }
    printf("no such node in linkedlist.");
    return NULL;
}

Node *lls_find_previous(LinkedList *lls, Node *t_node)
{
    if (t_node == lls->head)
    {
        return NULL;
    }

    for (Node *p = lls->head; p; p = p->next)
    {
        if (p->next == t_node)
        {
            return p;
        }
    }
    return NULL; // if t_node is head: return NULL;
}

Node *lls_pop_head(LinkedList *lls)
{
    if (lls->head)
    {
        Node *p = lls->head;
        lls->head = lls->head->next;
        lls->len--;
        return p;
    }
    puts("headless linkedlist.");
    return NULL;
}

Node *lls_pop_tail(LinkedList *lls)
{

    if (!lls->head->next)
    {
        return lls_pop_head(lls);
    }

    for (Node *p = lls->head, *e; p; p = p->next)
    {
        if (p->next->next == NULL)
        {
            e = p->next;
            p->next = NULL;
            lls->len--;
            return e;
        }
    }

    return NULL;
}

Node *lls_pop_value(LinkedList *lls, int v)
{
    Node *n;
    Node *pv_n;

    if (lls->head->v == v)
    {
        return lls_pop_head(lls);
    }

    for (Node *p = lls->head; p; p = p->next)
    {

        if (p->next->v == v)
        {
            pv_n = p;
            n = p->next;
            pv_n->next = n->next;
            lls->len--;
            return n; // 1st occurence
        }
    }
    return NULL;
}

Node *lls_pop_node(LinkedList *lls, Node *node)
{
    // if !(lls_find_node(node) && lls) {
    //     return NULL
    // }
    if (lls->head == node)
    {
        return lls_pop_head(lls);
    }
    for (Node *p = lls->head, *n; p; p = p->next)
    {
        if (p->next == node)
        {
            n = p->next;
            p->next = p->next->next;
            lls->len--;
            return n;
        }
    }
    return NULL;
}

void lls_inserta(LinkedList *lls, Node *t_node, Node *i_node)
{
    if (!lls_find_node(lls, t_node))
    {
        return;
    }

    if (t_node->next && i_node->next)
    {
        puts("ERROR: t_node and i_node both are not independent.");
        return;
    }

    i_node->next = t_node->next ? t_node->next : i_node->next;
    t_node->next = i_node;
    lls->len++;
    return;
}

void lls_remove(LinkedList *lls, Node *node)
{
    Node *rm = lls_pop_node(lls, node);
    if (rm)
    {
        node_release(rm);
    }
    return;
}

void lls_print(LinkedList *lls)
{
    // printf("lls len: %zu\n", lls->len);
    for (Node *p = lls->head; p; p = p->next)
    {
        printf("[%i]->", p->v);
    }
    printf("| <len: %zu>\n", lls->len);
    return;
}

void lls_reverse(LinkedList *lls)

{
    Node *t = lls_tail(lls);
    Node *pv_t;

    while ((pv_t = lls_find_previous(lls, t)))
    {
        pv_t = lls_pop_node(lls, pv_t);
        lls_append_as_tail(lls, pv_t);
    }
    return;
}

// ===============
int main()
{

    LinkedList *lls = lls_init(1);

    lls_append(lls, node_init(2));
    Node *z = node_init(0);
    lls_push(lls, z);
    Node *f = node_init(5);
    Node *f2 = node_init(5);
    lls_inserta(lls, z, f);
    lls_print(lls);
    printf("lls_find_value 2: %i\n", lls_find_value(lls, 2)->v);
    printf("lls_find_value 8: %p\n", lls_find_value(lls, 8));
    printf("lls_find_previous 5: %i\n", lls_find_previous(lls, f)->v);   // 0
    printf("lls_find_previous 5 (*): %p\n", lls_find_previous(lls, f2)); // 0x0
    lls_pop_head(lls);
    puts("pop head:");
    lls_print(lls);
    lls_pop_tail(lls);
    puts("pop tail:");
    lls_print(lls);
    lls_pop_value(lls, 5);
    puts("pop value 5: ");
    lls_print(lls);
    lls_pop_value(lls, 1);
    puts("pop value 1: ");
    lls_print(lls);
    lls_append(lls, node_init(1));
    lls_append(lls, node_init(2));
    lls_append(lls, node_init(3));
    lls_print(lls);
    puts("reverse:");
    lls_reverse(lls);
    lls_print(lls);
    lls_release(lls);

    return 0;
}

// a = [0]->[1]
// b = [2]->[3] << tail
// a append to b
// [2] -> [3] -> [0] -> [1]
