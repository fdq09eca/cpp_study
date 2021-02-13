#include <stdio.h>

void print_int(int v)
{
    if (v == 0)
    {
        putc('0', stdout);
        return;
    }
    if (v < 0)
    {
        putc('-', stdout);
        v = -v;
    }

    int div = 1;
    int tmp = v;

    while (tmp != 0)
    {
        tmp /= 10;
        div *= 10;
    }
    div /= 10;

    while (div > 0)
    {
        char ch = (v / div) % 10 + '0';
        putc(ch, stdout);
        div /= 10;
    }
}

int main()
{
    print_int(876);

    return 0;
}
