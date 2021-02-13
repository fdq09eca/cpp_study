#include <stdio.h>

size_t my_strlen(const char *s)
{
    size_t c = 0;
    for(;*s;s++, c++);
    // while (*s++)
    // {
    //     c++;
    // }
    return c;
}

int main(void)
{
    const char str[] = "1234";
    printf("without null character: %zu\n", my_strlen(str));
    printf("with null character:    %zu\n", sizeof str);
}