int parse_int(char *s)
{
    if (!s)
        return 0;

    for (; *s == ' ' || *s == '\t'; s++)
    {
        // trim spaces
    }

    int neg = 0;
    int v = 0;

    if (*s == '-')
    {
        neg = 1;
        s++;
    }
    else if (*s == '+')
    {
        // positive
    }

    for (; *s; s++)
    {
        char ch = *s;
        if (ch >= '0' && ch <= '9')
        {
            v *= 10;
            v += ch - '0';
        }
    }

    if (neg)
    {
        v = -v;
    }

    return v;
}