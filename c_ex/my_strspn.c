#include <stdio.h>
size_t my_strspn( const char *dest, const char *src ); 

int main(void)
{
    const char *string = "abcde312$#@aaaaaaaaaaaaaaaa";
    const char *low_alpha = "qwertyuiopasdfghjklzxcvbnm";
    size_t spnsz = my_strspn(string, low_alpha);
    printf("spnsz:%zu\n", spnsz);
    printf("After skipping initial lowercase letters from '%s'\n"
           "The remainder is '%s'\n", string, string+spnsz);
}

size_t my_strspn( const char *dest, const char *src ){
    int c = 0;
    for (char* d = (char*) dest; *d; d++) {
        for (char* s = (char*) src; *s; s++){
            if (*s == *d) {
                c++;
                break;
            } 
            if (c && !*(s + 1)) {
                return c;
            }                        
        }
    }
    return 0;
}