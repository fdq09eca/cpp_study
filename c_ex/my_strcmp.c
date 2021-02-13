#include <stdio.h>

int my_strcmp(const char *lhs, const char *rhs);

void demo(const char *lhs, const char *rhs)
{
    int rc = my_strcmp(lhs, rhs);
    if (rc == 0)
        printf("[%s] == [%s]\n", lhs, rhs);
    else if (rc < 0)
        printf("[%s] < [%s]\n", lhs, rhs);
    else if (rc > 0)
        printf("[%s] > [%s]\n", lhs, rhs);
}
int main(void)
{
    demo("ABC", "A!");
    demo("A!", "ABC");

    demo("ABC", "A");
    demo("A", "ABC");
    demo("A!", "A!");

    demo("", "");
    demo("", "A");
    demo("A", "");
}
int my_strcmp(const char *lhs, const char *rhs)
{
    while (*lhs)
    {
        if (*lhs == *rhs)
        {
            lhs++;
            rhs++;
        }
        else
        {
            break;
        }
    }
    return *(const unsigned char *)lhs - *(const unsigned char *)rhs;
}