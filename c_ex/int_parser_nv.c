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
    int neg = 0;
    if (*s == '-')
    {
        neg = 1;
        s++;
        l--;
    }

    int output = 0;

    while (l > 0)
    {
        l--;
        int i = *s - 48;

        if (neg)
        {
            output -= i * my_pow(10, l);
        }
        else
        {
            output += i * my_pow(10, l);
        }

        s++;
    }

    return output;
}

int main()
{
    // printf("%i", my_pow(2, 3));
    char *s = "-1234";

    int i = parse_int(s);

    printf("%i", i);

    return 0;
}