#include <stdio.h>

char *my_strncpy(char *dest, char *src, size_t n)
{
    char *d = dest;
    while (n--)
    {
        *dest++ = *src? *src++ : *src;
        // if (*src)
        // {
        //     *dest++ = *src++;
        // }
        // else
        // {
        //     *dest++ = 0;
        // }
    }
    return d;
}

int main()
{
    char src[] = "hi";
    char dest[6] = "abcdef";  // no null terminator
    my_strncpy(dest, src, 5); // writes five characters 'h', 'i', '\0', '\0', '\0' to dest
    printf("strncpy(dest, src, 5) to a 6-byte dest gives : ");
    for (size_t n = 0; n < sizeof dest; ++n)
    {
        char c = dest[n];
        c ? printf("'%c' ", c) : printf("'\\0' ");
    }
    printf("\nstrncpy(dest2, src, 2) to a 2-byte dst gives : ");
    char dest2[2] = {'?', '?'};
    my_strncpy(dest2, src, 0); // truncation: writes two characters 'h', 'i', to dest2
    for (size_t n = 0; n < sizeof dest2; ++n)
    {
        char c = dest2[n];
        c ? printf("'%c' ", c) : printf("'\\0' ");
    }
    printf("\n");
}