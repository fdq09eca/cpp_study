#include <stdio.h>

char *my_strcpy(char *dest, const char *src)
{
    char *d = dest;
    while ((*dest++ = *src++))
        ;

    return d;
}

// int main()
// {
//     char arr[10];
//     my_strcpy(arr, "hello");
//     printf("%s\n", arr);
//     return 0;
// }

// https://github.com/freebsd/freebsd-src/blob/master/lib/libc/string/strcpy.c
