#include <stdio.h>

char *my_strcpy(char *dest, const char *src);
char *my_strcat(char *dest, const char *src);

int main()
{
    char str[50] = "Hello ";
    char str2[50] = "World!";
    my_strcat(str, str2);
    my_strcat(str, " ...");
    my_strcat(str, " Goodbye World!");
    puts(str);
    return 0;
}

char *my_strcat(char *dest, const char *src)
{
    char *d = dest;
    for (; *d; d++)
    {
        // dest null terminator found.
    }
    my_strcpy(d, src);
    return dest;
}