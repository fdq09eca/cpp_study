#include <stdio.h>

char * my_strchr ( const char *, int );

int main(void)
{
    const char *str = "Try not. Do, or do not. There is no try.";
    char target = 'T';
    const char *result = str;

    while ((result = my_strchr(result, target)) != NULL)
    {
        printf("Found '%c' starting at '%s'\n", target, result);
        ++result; // Increment result, otherwise we'll find target at the same location
    }
}

char *my_strchr(const char *str, int ch)
{
    char c = (char) ch;
    for (; *str; str++){
        if (*str == c){
            return (char*) str;
        }
    }
    return NULL;
}