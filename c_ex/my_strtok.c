#include <stdio.h>
#include <string.h>
char *my_strtok_r(char *str, char *delim, char **save);
char *my_strtok_s(char *str, size_t *strmax, char *delim, char **save);
char *my_strtok(char *token, size_t token_size, char *str, char *delim, char **save);

    int main()
{
    char str[] = ",.-,BB,,CC";
    char token[100];
    size_t token_size = 100;
    char *save;
    char *delim = ",.-";

    // while (token = my_strtok(str, " ", &rest))
    // {
    // printf("%s\n", my_strtok(str, ",.-", &save));
    // printf("%s\n", my_strtok(NULL, ",.-", &save));
    // printf("%s\n", my_strtok(NULL, ",.-", &save))`;
    // printf("%s\n", my_strtok(NULL, ",.-", &save));
    //}
    printf("%s\n", my_strtok(token, 100, str, delim, &save));
    printf("%s\n", my_strtok(token, 100, NULL, delim, &save));
    printf("%s\n", my_strtok(token, 100, NULL, delim, &save));
    printf("%s\n", my_strtok(token, 100, NULL, delim, &save));

    return 0;
}

int is_delim(char ch, char *delim)
{
    for (char *d = delim; *d; d++)
    {
        if (ch == *d)
            return 1;
    }
    return 0;
}

char *my_strtok(char *token, size_t token_size, char *str, char *delim, char **save)
{
    // static char token[100];
    char *s = str ? str : *save;
    if (!s)
        return NULL;
    char *t = token;

    for (; strchr(delim, *s); s++)
    { /* trim delim*/
    }
    size_t output_size = 0;
    for (; *s; s++)
    {
        if (strchr(delim, *s))
            break;
        if (output_size >= token_size)
            return NULL;

        *t = *s;
        t++;
        output_size++;
    }
    *save = *s ? s + 1 : NULL;

    if (output_size >= token_size)
        return NULL;
    *t = 0;

    return token;
}