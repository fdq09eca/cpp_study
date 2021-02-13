#include <stdio.h>
char *my_strcaserstr(const char *str, const char *substr);

void find_str(char const *str, char const *substr)
{
    char *pos = my_strcaserstr(str, substr);
    if (pos)
    {
        printf("found the string '%s' in '%s' at position: %ld\n", substr, str, pos - str);
    }
    else
    {
        printf("the string '%s' was not found in '%s'\n", substr, str);
    }
}

int main(void)
{
    
    char *str = "abc123A";
    find_str(str, "a"); // 6
    find_str(str, "23a");// 4
    find_str(str, "2a"); //null 
    find_str(str, ""); //null <<?
    return 0;
}

char my_tolower(char s) {
    if (s >= 'A' && s <= 'Z') {
        return s - 'A' + 'a';
    }
    return s;
}

char *my_strcaserstr(const char *str, const char *substr)
{
    if (!*substr) {
        return NULL;
    }

    char* r = NULL;

    for (; *str; str++)
    {
        char *s = (char *)str;
        char *ss = (char *)substr;
        for (; *s && *ss; s++, ss++)
        {
            if (my_tolower(*s) != my_tolower(*ss)) 
                break;
        }
        if (!*ss)
            r = (char *)str;
    }
    return r;
}

