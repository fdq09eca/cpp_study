#include <stdio.h>

char *my_strrchr( const char *str, int ch ); 

int main(void)
{
    char s[] = "7\07";
    printf("s0: %p, 7: %p\n", s, my_strrchr(s, '7'));
    
}

char *my_strrchr( const char *str, int ch ){
    char* s = (char*) str;
    
    for (;*str; str++){
        // to null terminator.
    }
    str--;
    char c = (char) ch;
    for (;str >= s; str-- ) {
        printf(" c = %d\n", *str);
        if (*str == c) return (char*) str;
    }
    return NULL;
}