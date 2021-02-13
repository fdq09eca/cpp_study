#include <stdio.h>

void *my_memset(void *dest, int ch, size_t count);

int main()
{
    char str[] = "ghghghghghghghghghghgh";
    puts(str);
    my_memset(str, 'a', 5);
    puts(str);
    return 0;
}

void *my_memset(void *dest, int ch, size_t count)
{
    char *d = dest;
    char *end = d + count;
    char c = (char)ch;
    for (; d < end; d++)
    {
        *d = c;
    }
    return dest;
}
