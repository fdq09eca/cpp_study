#include <iostream>

#define TEST(EXPR)                                                                  \
    do                                                                              \
    {                                                                               \
        printf("[%s] Line %3d: %s\n", ((EXPR) ? " OK " : "FAIL"), __LINE__, #EXPR); \
    } while (0) //-------------------

class Node
{
private:
    Node *prev;
    Node *next;
    friend class DoublyLinkedList;

public:
    int v;

    Node() : prev(nullptr), next(nullptr){};

    Node(int v_) : prev(nullptr), next(nullptr), v(v_){};

    ~Node()
    {
        std::cout << "Node->v: " << v << " destructed\n";
    }
};

class DoublyLinkedList
{
public:
    Node *head;
    Node *tail;
    size_t len;

    DoublyLinkedList() : head(nullptr), tail(nullptr), len(0){};

    ~DoublyLinkedList(){
        clear();
        std::cout << "LinkedList destructed.\n";
    }

    void clear(){
        Node* p;
        while ((p = pop_head())) {
            delete p;
        }
        std::cout << "LinkedList cleared.\n";
    }

    Node* insert(int v_) {
        return insert_after(nullptr, v_);
    }

    Node* append(int v_) { return insert_after(tail, v_); }

    Node* find(int v_) {
        for (Node* p = head; p ; p=p->next) {
            if (p->v == v_) return p;
        }
        return nullptr;
    }

    Node* pop_head() { return remove(head); }
    
    Node* pop_tail() { return remove(tail); }

    Node* remove(Node* target_node){
        if (!target_node) {
            return nullptr;
        }
        
        if (target_node->prev) {
            target_node->prev->next = target_node->next;     // <<
        } else {
            head = target_node->next;
        }

        if (target_node->next) {
            target_node->next->prev = target_node->prev; // <<
        } else {
            tail = target_node->prev;
        }
        
        target_node->prev = nullptr;
        target_node->next = nullptr;
        len --;
        
        return target_node;
    }
    

    Node* insert_after(Node *target_node, Node* new_node)
    {
        if (!target_node)
        {
            if (head) {
                new_node->next = head;
                head->prev = new_node;
            } else {
                tail = new_node;
            }
            head = new_node;
        } else {
            if (target_node->next) {
                // T <- N <- Tn: 102, 104
                // T -> N -> Tn: 103, 105
                new_node->prev = target_node;
                new_node->next = target_node->next;
                target_node->next->prev = new_node;
                target_node->next = new_node;
            } else {
                // tail
                new_node->prev = target_node;
                target_node->next = new_node;
                tail = new_node;

            }
        }
        len++;
        return new_node;
        
    }

    Node* insert_after(Node *target_node, int v_)
    {
        Node *new_node = new Node(v_);
        return insert_after(target_node, new_node);
    }
    
    Node* insert_after(int t_, int v_)
    {
        Node *new_node = new Node(v_);
        Node* target_node = find(t_);
        return insert_after(target_node, new_node);
    }
    
    void print()
    {
        std::cout <<"next: ";
        Node *p = head;
        while (p)
        {
            std::cout << p->v << "->";
            p = p->next;
        }
        std::cout << "|<" << len << ">\n";
    }

    void print_r()
    {
        std::cout <<"prev: ";
        Node *p = tail;
        while (p)
        {
            std::cout << p->v << "->";
            p = p->prev;
        }
        std::cout << "|<" << len << ">\n";
    }
};

int main()
{
    DoublyLinkedList dll;
    
    std::cout<<"==TEST PUSH HEAD ==\n";
    for (int i = 1; i <= 10; i++)
    {
        dll.insert_after(nullptr, i);
    }
    dll.print();
    dll.print_r();
    
    dll.clear();
    
    std::cout<<"== TEST PUSH TAIL ==\n";
    for (int i = 1; i <= 10; i++)
    {
        dll.insert_after(dll.tail, i);
    }
    dll.print();
    dll.print_r();
    dll.clear();
    
    std::cout<<"== TEST INSERT AFTER ==\n";
    Node* p = nullptr;
    
    for (int i = 1; i <= 10; i++)
    {

        p = dll.insert_after(p, i);
    }

    dll.print();
    dll.print_r();
    dll.clear();

    std::cout<<"== TEST INSERT MIDDLE ==\n";
    p = dll.insert(0);
    dll.append(2);
    dll.insert_after(p, 1);
    dll.print();
    dll.print_r();
    dll.clear();

    std::cout<<"== TEST POP HEAD/TAIL ==\n";
    p = dll.insert(0);
    dll.pop_head();
    dll.print();
    dll.pop_head();
    dll.print();
    dll.pop_tail();
    dll.print();
    
    p = dll.append(0);
    dll.pop_tail();
    dll.print();
    dll.pop_head();
    dll.print();
    dll.pop_head();
    dll.print();
    dll.print();
    return 0;
}