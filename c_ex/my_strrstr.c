#include <stdio.h>
char *my_strrstr(char const *str, char const *substr);

int main(void)
{
    
    printf("%s\n", my_strrstr("", "11"));
    printf("%s\n", my_strrstr("11", "14"));
    printf("%s\n", my_strrstr("11", "213"));
    printf("%s\n", my_strrstr("11", "21"));
    printf("%s\n", my_strrstr("111 112 113 114 115 116", "11"));
    printf("%s\n", my_strrstr("111 112 113 114 115 116", "12"));
    return 0;
}

char *my_strrstr(char const *str, char const *substr)
{
    if (!*substr) {
        return NULL;
    }
    
    char *r = NULL;
    for (; *str; str++)
    {
        char *s = (char *)str;
        char *ss = (char *)substr;
        for (;*s && *ss; s++, ss++){
            if (*s != *ss) {
                break;
            }
        }
        if (!*ss)
        {
            r = (char *)str;
        }
    }
    
    return r;
}