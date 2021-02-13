#include <stdio.h>

void skip_ch(char **c, char ch);
int parse_int(const char **c);
void print_int(int v, int pad, int z_pad);
void print_str(char *str, int pad, int z_pad);
void my_printf(const char *fmt, int p0, char *p1);

int main()
{
    int a = 10;
    char *s = "ABCDE";

    my_printf("a=[%d] s=[%s]\n", a, s);
    my_printf("a=[%2d] s=[%2s]\n", a, s);
    my_printf("a=[%4d] s=[%10s]\n", a, s);
    my_printf("a=[%04d] s=[%05s]\n", a, s);
    my_printf("a=[%00004d] s=[%000010s]\n", a, s);

    return 0;
}

void my_printf(const char *fmt, int p0, char *p1)
{

    int f = 0; // Chris: it is ugly
    for (const char *c = fmt; *c; c++)
    {
        if (*c == '%')
        {
            int z_pad = 0;
            int pad = 0;

            f++;
            c++; // check next char

            if (!*c)
            {
                puts(">> wrong format");
                return;
            }

            if (*c == '%') // ecaspe char %
            {
                putchar(*c);
                continue;
            }

            if (*c == '0')
            {
                z_pad = 1;
                // skip_ch(&c, '0'); // trim zero
            }

            pad = parse_int(&c);
            // printf("c: %c, pad: %i",*c,  pad);

            if (f == 1 && (*c == 'd' || *c == 'i')) // << hard coded position..? any improvement? enum? how?
            // va_list(list, int)
            {
                print_int(p0, pad, z_pad);
                continue;
            }

            if (f == 2 && *c == 's')
            {
                print_str(p1, pad, z_pad);
                continue;
            }
        }

        putchar(*c);
    }
}

int parse_int(const char **c)
{
    int v = 0;
    for (; **c >= '0' && **c <= '9'; (*c)++)
    {
        v *= 10;
        v += **c - '0';
    }
    return v;
}

int n_digit(int v)
{
    int n = 0;
    while (v)
    {
        v /= 10;
        n++;
    }
    return n;
}

void print_n_ch(int n, char c)
{
    for (int i = 0; i < n; i++)
    {
        putchar(c);
    }
}

void print_pad(int s_len, int pad, int z_pad)
{
    int p = pad - s_len;
    if (p)
    {
        char ch = z_pad? '0':' ';
        print_n_ch(p, ch);
    }
}

void print_int(int v, int pad, int z_pad)
{
    int div = 1;
    int n = n_digit(v);

    print_pad(n, pad, z_pad);

    while (n)
    {
        div *= 10;
        n--;
    }
    div /= 10;

    while (div > 0)
    {
        char ch = (v / div) % 10 + '0';
        putchar(ch);
        div /= 10;
    }
}

void print_str(char *str, int pad, int z_pad)
{
    int len = 0;

    for (char *s = str; *s; s++)
    {
        len++;
    }

    print_pad(len, pad, z_pad);

    for (char *s = str; *s; s++)
    {
        putchar(*s);
    }
}
