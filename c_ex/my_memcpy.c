#include <stdio.h>
void *my_memcpy(void *dest, const void *src, size_t count);
int main()
{ // simple usage
    // char source[] = "once upon a midnight dreary...", dest[4];
    // my_memcpy(dest, source, sizeof dest);
    // for (size_t n = 0; n < sizeof dest; ++n)
    //     putchar(dest[n]);
    char str[] = "0123456789";
    my_memcpy(str + 4, str + 3, 3);

    // printf("str+ 4: %c, str+ 3: %c\n", *(str + 4), *(str + 3));
    printf("%s\n", str);
    return 0;
}

void *my_memcpy(void *dest, const void *src, size_t count)
{
    //
    char *d = (char *)dest;
    char *s = (char *)src;
    char *end = d + count;
    for (; d < end; d++, s++)
    {
        *d = *s;
    }
    return dest;
}

/*
1 2 3 4 5 6 7 8 9 0
    s d     e
1 2 3 3 3 3 3 8 9 0
*/