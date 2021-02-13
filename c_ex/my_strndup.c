#include <stdio.h>
#include <stdlib.h>

char *my_strndup(const char *str1, size_t n);

int main(void)
{
    const size_t n = 3;

    const char *src = "Replica";
    char *dup = my_strndup(src, n);
    printf("my_strndup(\"%s\", %lu) == \"%s\"\n", src, n, dup);
    free(dup);

    src = "Hi";
    dup = my_strndup(src, n);
    printf("my_strndup(\"%s\", %lu) == \"%s\"\n", src, n, dup);
    free(dup);

    const char arr[] = {'A', 'B', 'C', 'D'}; // NB: no trailing '\0'
    dup = my_strndup(arr, n);
    printf("my_strndup({'A','B','C','D'}, %lu) == \"%s\"\n", n, dup);
    free(dup);
}

/*
 OUTPUT: 
 strndup("Replica", 3) == "Rep"
 strndup("Hi", 3) == "Hi"
 strndup({'A','B','C','D'}, 3) == "ABC" 
*/

char *my_strndup(const char *str1, size_t n)
{
    // char *s = str1;
    // size_t slen;
    // for (; *s; slen++, s++)
    //     ;

    char *dup_ns = (char *)malloc((n + 1) * sizeof(char));

    if (!dup_ns)
    {
        return NULL;
    }

    char *d = dup_ns;
    while (n--)
    {
        *dup_ns++ = *str1 ? *str1++ : 0;
    }
    *dup_ns = 0;
    return d;
}