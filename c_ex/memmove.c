#include <stdio.h>

void *my_memmove(void *dest, const void *src, size_t count);

int main()
{
    char str0[] = "1234567890";
    char str__[] = "1234567890";
    char x[] = {'A', 'B', 'C'};

    my_memmove(str__, x, 3); // copy from [A,B,C] to [1,2,3]
    printf("%s, copy from [A,B,C] to [1,2,3]: %s\n", str0, str__);

    char str1[] = "1234567890";
    my_memmove(str1 + 3, str1 + 4, 3); // copy from [5,6,7] to [4,5,6]
    printf("%s, copy from [5,6,7] to [4,5,6]: %s\n", str0, str1);

    char str2[] = "1234567890";
    my_memmove(str2 + 4, str2 + 3, 3); // copy from [4,5,6] to [5,6,7]
    printf("%s, copy from [4,5,6] to [5,6,7]: %s\n", str0, str2);

    char str3[] = "1234567890";
    my_memmove(str3, str3, 3);
    printf("%s, copy from [1,2,3] to [1,2,3]: %s\n", str0, str3);

    /////
    // char str__[] = "1234567890";
    // char x[] = {'A','B','C'};
    // memmove(str__, x, 3); // copy from [A,B,C] to [1,2,3]
    // printf("%s, copy from [A,B,C] to [1,2,3]: %s\n", str0, str__);

    // char str1[] = "1234567890";
    // memmove(str1 + 3, str1 + 4, 3); // copy from [5,6,7] to [4,5,6]
    // printf("%s, copy from [5,6,7] to [4,5,6]: %s\n", str0, str1);

    // char str2[] = "1234567890";
    // memmove(str2 + 4, str2 + 3, 3); // copy from [4,5,6] to [5,6,7]
    // printf("%s, copy from [4,5,6] to [5,6,7]: %s\n", str0, str2);

    // char str3[] = "1234567890";
    // memmove(str3, str3, 3);
    // printf("%s, copy from [1,2,3] to [1,2,3]: %s\n", str0, str3);

    return 0;
}

void *my_memmove(void *dest, const void *src, size_t count)
{
    if (dest == src)
    {
        return (void *)dest;
    }

    char *d = (char *)dest;
    char *s = (char *)src;
    char *end = d + count;
    int overlapped = 0;

    if ((s < d && s + count > d) || (d < s && d + count > s))
    {
        // printf("OVERLAPPED!!\n");
        overlapped = 1;
    }

    if (overlapped && src < dest)
    {
        d = end - 1;
        s += count - 1;
        for (int i = 0; d >= (char *)dest; d--, s--, i++)
        {
            // printf("%i, *d: %c, *s = %c\n", i, *d, *s);
            *d = *s;
        }
        return (void *)dest;
    }

    for (int i = 0; d < end; d++, s++, i++)
    {
        // printf("%i, *d: %c, *s = %c\n", i, *d, *s);
        *d = *s;
    }

    return (void *)dest;
}