#include <stdio.h>

int my_strncmp(const char *lhs, const char *rhs, size_t n);

void demo(const char *lhs, const char *rhs, size_t n)
{
    int rc = my_strncmp(lhs, rhs, n);
    if (rc == 0)
        printf("<%zu>: [%s] == [%s]\n", n, lhs, rhs);
    else if (rc < 0)
        printf("<%zu>: [%s] < [%s]\n", n, lhs, rhs);
    else if (rc > 0)
        printf("<%zu>: [%s] > [%s]\n", n, lhs, rhs);
}
int main(void)
{
    demo("ABC", "AE", 1);
    demo("AE", "ABC", 2);

    demo("ABC", "A", 3);
    demo("A", "ABC", 4);
    demo("A!", "A!", 1);

    demo("", "", 0);
    demo("", "A", 1);
    demo("A", "", 1);
}
int my_strncmp(const char *lhs, const char *rhs, size_t n) {
    if (!n) return 0; //early rejection
    while (*lhs) {
        if (*lhs != *rhs) break;
        if (!--n) return 0;
        lhs++; rhs++;
    }
    return *(const unsigned char*)lhs - *(const unsigned char*)rhs;
}