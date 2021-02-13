#include <stdio.h>

void print_int(int i)
{
    int l = 0;
    char arr[20];
    while (i != 0)
    {
        char c = (char)(i % 10 + '0');
        arr[l] = c;
        l++;
        i /= 10;
    }

    for (int j = l; j >= 0; j--)
    {
        printf("%c", arr[j]);
    }

    // printf("%i",l);
}

int main()
{
    int i = 1234;
    print_int(i);
}
