#include <stdio.h>
#include <string.h>
char *my_strpbrk(const char *, const char *);

int main()
{
    char str[] = "This is a sample string";
    char key[] = "aeiou";
    char *pch;
    printf("Vowels in '%s': ", str);
    pch = my_strpbrk(str, key);
    while (pch != NULL)
    {
        printf("%c ", *pch);
        pch = my_strpbrk(pch + 1, key);
    }
    printf("\n");
    return 0;
}

char *my_strpbrk(const char *s1, const char *s2)
{
    for (; *s1; s1++)
    {
        for (const char* t = s2; *t; t++)
        {
            if (*s1 == *t)
                return (char*) s1;
        }
    }
    return NULL;
}