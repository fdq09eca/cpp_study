# HW

- try to use [variadic arguments](https://en.cppreference.com/w/c/variadic) i.e. `...` to do `my_printf` again?

![](ll.png)

- linked list
  - [x] insert(Node* n) (after): `inserta`
  - [x] push head: `push`
  - [x] push tail: `append`
  - [x] remove(Node* n)
  - [x] Node* pop_head: `lls_pop_head`
  - [x] Node* pop_tail: `lls_pop_tail`
  - [x] void reverse()
  - [x] find(int v) `find`
  
- doubly linked list
  - insert(Node* n) (after)
  - remove(Node* n)
  - Node* pop_head(MyList)
  - Node* pop_tail()
  - void reverse()
  - Node* find(int v)

- dynamic array
  - insert(idx, int)
  - append(int)
  - void remove_at(idx)
  - int remove(int)
  - idx find(int)
  - selection_sort

- black jack.
  - number of Deck?
  - number of Player (Max 8)? 3
- text-ui prototype:
  - Player1 $: inital $ -> 100
  - Player2 $: inital $ -> 100
  - Player3 $: inital $ -> 100
  - $: 0
  - Bet: 10
  - Dealer: 9s
  - Player: Qh, As
    - win rate: `BJ? bet * 1.5 : bet;`
  - Player: more card? \[Y/N\]
  - Player: split [Y/N]
  - Player: double bet [Y/N] 

---

## done ex [^cpp]

- [x] [str_int_parser](./int_parser.c)
- [x] [int_str_convert](./int_str_convert.c): [j_int_parser](./j_int_str_convert.c)
- [x] [my_strcpy](./my_strcpy.c): [cppref](https://en.cppreference.com/w/c/string/byte/strcpy), [fdsb_strcpy](https://github.com/freebsd/freebsd-src/blob/master/lib/libc/string/strcpy.c)
- [x] [my_strncpy](./my_strncpy.c): [cppref](https://en.cppreference.com/w/c/string/byte/strncpy), [fbsd_strncpy](https://github.com/freebsd/freebsd-src/blob/master/lib/libc/string/strncpy.c)
- [x] [my_strlen](./my_strlen.c): [cppref](https://en.cppreference.com/w/c/string/byte/strlen), [fbsd_strlen](https://github.com/freebsd/freebsd-src/blob/master/lib/libc/string/strlen.c#L111)
- [x] [my_strcat](./my_strcat.c)[^p1] [^a1]: [cppref](https://en.cppreference.com/w/c/string/byte/strcat) [fbsd_strcat](https://github.com/freebsd/freebsd-src/blob/master/lib/libc/string/strcat.c)
- [x] [my_strdup](./my_strdup.c): [cppref](https://en.cppreference.com/w/c/string/byte/strdup), [freebsd_strdup](https://github.com/freebsd/freebsd-src/blob/master/lib/libc/string/strdup.c)
- [x] [my_strndup](./my_strndup.c): [cppref](https://en.cppreference.com/w/c/string/byte/strndup), [freebsd_strndup](https://github.com/freebsd/freebsd-src/blob/master/lib/libc/string/strndup.c)
- [x] [my_strcmp](./my_strcmp.c): [cppref](https://en.cppreference.com/w/c/string/byte/strcmp), [freebsd_strcmp](https://github.com/freebsd/freebsd-src/blob/master/lib/libc/string/strcmp.c)
- [x] [my_strncmp](./my_strncmp.c): [cppref](https://en.cppreference.com/w/c/string/byte/strncmp), [freebsd_strncmp](https://github.com/freebsd/freebsd-src/blob/master/lib/libc/string/strncmp.c)
- [x] [my_strchr](./my_strchr.c): [cppref](https://en.cppreference.com/w/c/string/byte/strchr), [freebsd_strchr](https://github.com/freebsd/freebsd-src/blob/master/lib/libc/string/strchr.c)
- [x] [my_strrchr](./my_strrchr.c): [cppref](https://en.cppreference.com/w/c/string/byte/strrchr), [freebsd_strrchr](https://github.com/freebsd/freebsd-src/blob/master/lib/libc/string/strrchr.c)
- [x] [my_strstr](./my_strstr.c): [cppref](https://en.cppreference.com/w/c/string/byte/strstr), [freebsd_strstr](https://github.com/freebsd/freebsd-src/blob/master/lib/libc/string/strstr.c)
- [x] [my_strrstr](./my_strrstr.c): no ref.
- [x] [my_strcasestr](./my_strcasestr.c) [^win_strcasestr]: [freebsd_strcasestr](https://github.com/freebsd/freebsd-src/blob/master/lib/libc/string/strcasestr.c)
- [x] [my_strcaserstr](./my_strcasestr.c): no ref.
- [x] [my_strspn](./my_strspn.c): [cppref](https://en.cppreference.com/w/c/string/byte/strspn), [freebsd_strspn](https://github.com/freebsd/freebsd-src/blob/master/lib/libc/string/strspn.c)
- [x] [my_strpbrk](./my_strpbrk.c): [cppref](https://en.cppreference.com/w/c/string/byte/strpbrk), [freebsd_strpbrk](https://github.com/freebsd/freebsd-src/blob/master/lib/libc/string/strpbrk.c)
- [x] [my_strtok](./my_strtok.c): [cppref](https://en.cppreference.com/w/c/string/byte/strtok), [freebsd_strtok](https://github.com/freebsd/freebsd-src/blob/master/lib/libc/string/strtok.c)
- [x] [my_memchr](./my_memchr.c): [cppref](https://en.cppreference.com/w/c/string/byte/memchr), [freebsd_memchr](https://github.com/freebsd/freebsd-src/blob/master/lib/libc/string/memchr.c)
- [x] [my_memset](./my_memset.c): [cppref](https://en.cppreference.com/w/c/string/byte/memset), [freebsd_memset](https://github.com/freebsd/freebsd-src/blob/master/lib/libc/string/memset.c)
- [x] [my_memcpy](./my_memcpy.c): [cppref](https://en.cppreference.com/w/c/string/byte/memcpy), [freebsd_memcpy](https://github.com/freebsd/freebsd-src/blob/master/lib/libc/string/memcpy.c)
- [x] [my_memmove](./my_memmove.c): [cppref](https://en.cppreference.com/w/c/string/byte/memmove), [freebsd_memmove](https://github.com/freebsd/freebsd-src/blob/master/lib/libc/string/memmove.c)
- [x] [my_printf](./my_printf.c): no_ref; given prototype: `void my_printf(const char *fmt, int p0, char *p1);`

[^1]: `static buffer`
[^p1]: Instead of doing the copy, I was thinking put the `char* src` at the `char* dest`'s null terminator position (as if linked list) but seems it is worng, why is it?
[^a1]: Because wrong type. `*dest` is `char`, not `char *`.
[^win_strcasestr]: Window version: `strcasestr` = `stristr`
[^restrict]: what does `restrict` mean?
[^cpp]: The following ex follow [cppreference.com](https://en.cppreference.com/w/c/string/byte).

## Note
- [varidic_arg](https://en.cppreference.com/w/c/variadic)
- 2d array formula = `rowIdx * numCol + colIdx`
- `fread` **does not** return the read value, see [doc](https://en.cppreference.com/w/cpp/io/c/fread).
- 1's complement, 2's complement
- POSIX
- calling convention
  - `printf("%d %d %d\n", i++, i++, i++);`
  - Mac: from left to right i.e. `2 1 0`
  - Window: from right to left, i.e. `0 1 2`
- Cross platform matters
  - `size_t` is `unsiged int type`: allow the user to input their respective allowed memory amount.
    - `printf` when it is 32bit (4 byte): `%u`; 64bit (8 byte): `%ull`
    - see Jason's [YouTube ref](https://www.youtube.com/watch?v=JiUfvzd4eQM)
  - `unsigned char`
- x86, x64
- `gcc`: GNU C Compiler
  - `gcc -o my_strcat my_strcat.c my_strcpy.c` compile 2 `.c` together, only 1 `main(){}`.
- `while (*s++){}` is different from `while (*s) {s++;}`
- `char[] str != char* str`, modify string literal results in undefine behaviour, see [here](https://en.cppreference.com/w/cpp/language/string_literal) and [here](https://stackoverflow.com/questions/10186765/what-is-the-difference-between-char-array-and-char-pointer-in-c).
- null terminator concept: **do not** rely on str length.

*DEBUG: print out the pointer, deref.*

```c
for (;str >= s; str-- ) {
        printf(" c = %d\n", *str);
}
```

*RESULT*

```sh
~/Documents/JCC(ex*) » make my_strrchr && ./my_strrchr                                                                                                                                          macone@Macs-MBP
cc     my_strrchr.c   -o my_strrchr
 c = 0
 c = 7
 c = 55
s0: 0x7ffeea48d59d, 7: 0x7ffeea48d59d
----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
~/Documents/JCC(ex*) » make my_strrchr && ./my_strrchr                                                                                                                                          macone@Macs-MBP
cc     my_strrchr.c   -o my_strrchr
 c = 7
 c = 55
s0: 0x7ffee3a5959d, 7: 0x7ffee3a5959d
```

