#include <stdio.h>
#include <stdlib.h>

char *my_strdup(const char *str1);

int main(void)
{
    char *s1 = "abc";
    char *s2 = my_strdup(s1);
    int i = 0;
    char *s = s2;
    while (1)
    {
        *s ? printf("'%i: %c'\n", i, *s) : printf("'%i: \\0'\n", i);
        if (!*s)
        {
            break;
        }
        s++;
        i++;
    }
    // printf("s2 = \"%s\"\n", s2);
    free(s2);
}

char *my_strdup(const char *str1)
{
    int c = 0;
    const char *s = str1;

    for (; *s; s++, c++)
    { //strlen cal
    };

    printf("strlen: %i\n", c);

    char *dup_s = (char *)malloc((c + 1) * sizeof(char));

    if (dup_s == NULL) // check malloc
    {
        return dup_s;
    }

    char *d = dup_s;
    while ((*dup_s++ = *str1++)) // it copys the null terminator as well.
    { 
    };
    return d;
}