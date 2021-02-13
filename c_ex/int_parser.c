#include <stdio.h>
int my_pow(int i, int p)
{
    int ans = 1;
    for (int j = 0; j < p; j++)
    {
        ans *= i;
    }
    return ans;
}

int str_len(char *s)
{
    int c = 0;
    while (*s != '\0')
    {
        s++;
        c++;
    }
    return c;
}

int parse_int(char *s)
{
    int l = str_len(s);
    
    int output = 0;
    while (l > 0)
    {
        l--;
        int i = *s - 48;
        output += i * my_pow(10, l);
        printf("%d\n", output);
        s++;
    }
    return output;
}

int main()
{
    // printf("%i", my_pow(2, 3));
    char *s = "1234";

    int i = parse_int(s);

    printf("%i", i);

    return 0;
}