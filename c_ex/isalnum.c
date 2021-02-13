#include <stdio.h>
int my_isalnum(int ch); //forward declaration

int main()
{
    char ch = 'a';
    printf("hello aaa%cbbb\n", 10);
    // printf("%i", my_isalnum(ch));
    return 0;
}

int my_isalnum(int ch)
{
    if (ch >= 'a' && ch <= 'z')
    {
        return 1;
    }
    if (ch >= 'A' && ch <= 'Z')
    {
        return 1;
    }
    if (ch >= '0' && ch <= '9')
    {
        return 1;
    }
    return 0;
};