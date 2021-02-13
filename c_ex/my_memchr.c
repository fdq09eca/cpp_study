#include <stdio.h>

void *my_memchr(const void *ptr, int ch, size_t count);

int main(void)
{
    char str[] = "ABCDEFG";
    char *ps = my_memchr(str, 'D', 5);
    if (ps != NULL)
        printf("search character found:%c\n", *ps);
    else
        printf("search character not found\n");

    return 0;
}

void *my_memchr(const void *ptr, int ch, size_t count)
{
    while (count)
    {
        if (*((unsigned char *)ptr) == (unsigned char)ch)
        {
            return (void *)ptr;
        }
        ptr++;
        count--;
    }
    return NULL;
}