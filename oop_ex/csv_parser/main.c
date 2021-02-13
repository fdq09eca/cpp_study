#include <stdio.h>
#include <stdlib.h>
#define CELL_SIZE 500
#define ROW_SIZE (CELL_SIZE * 10)

typedef struct
{
    char *data;
    size_t cell_n;
} CELL;

typedef struct
{
    char *data;
    size_t n_cell;
    size_t row_n;
    CELL *cells;
} ROW;

typedef struct
{
    char *filename;
    char *data;
    size_t n_row;
    ROW *rows;
} CSV;

char *file_ext(const char *fn);
int my_strcmp(const char *str1, const char *str2);
int is_csv(const char *fn);
FILE *open_csv(const char *fn, char *);
size_t file_size(FILE *f);
char *read_csv(const char *fn);
void init_csv(CSV *csv, char *fn);
void free_csv(CSV *csv);
char *parse_row(CSV *csv, char **save);
void print_rows(CSV *csv);
void print_csv(CSV *csv);
char *nextchr(char *str, char ch);
ROW *get_row(CSV *csv, size_t r);
CELL *get_cell(CSV *csv, size_t r, size_t c);
void debug_print(CSV *csv);

int main()
{
    CSV csv;
    init_csv(&csv, "test.csv");
    debug_print(&csv);
    // print_csv(&csv);
    // ROW *r = get_row(&csv, 1);
    // printf(">> row %zu: %s\n", r->row_n, r->data);
    // CELL *c = get_cell(&csv, 1, 0);
    // printf(">> cell %zu: %s\n", c->cell_n, c->data);
    // print_csv(&csv);
    free_csv(&csv);
    return 0;
}

size_t n_cell(ROW *row)
{
    size_t n = 0;
    for (char *c = row->data; *c; c++)
    {
        if (*c == '"')
        {
            c = nextchr(c, '"');
        }
        if (*c == ',')
        {
            n++;
        }
    }
    return n + 1;
}
// buff[500]
// buff[10]=> cell[10]

char *parse_cell(ROW *row, char **save)
{
    char *buff = malloc(CELL_SIZE * sizeof(char));

    char *b = buff;
    char *c = *save ? *save : row->data;

    int dq = 0;
    for (;; c++, b++)
    {
        if (*c == '"')
        {
            dq++;
        }
        *b = *c;
        if (*c == ',' || *c == '\0')
        {
            if (dq % 2)
            {
                continue;
            }
            *b = '\0';
            *save = c + 1;
            return buff;
        }
    }
    free(buff);
    return NULL;
}

void init_cell(CELL *cell, size_t n, char *data)
{
    cell->cell_n = n;
    cell->data = data;
    return;
}

void load_cell(ROW *row)
{
    size_t row_n = row->row_n;
    CELL *cell = row->cells;
    CELL *end = cell + row->n_cell;
    char *save = NULL;
    for (int n = 0; cell < end; cell++, n++)
    {
        char *data = parse_cell(row, &save);
        if (!data)
        {
            break;
        }
        // printf("load cell%zu%i: %s\n", row_n, n, data);
        init_cell(cell, n, data);
    }
    return;
}

size_t n_row(CSV *csv)
{
    size_t n = 0;
    size_t dq = 0;
    for (char *c = csv->data; *c; c++)
    {
        if (*c == '"')
        {
            dq++;
        }
        if (*c == '\n')
        {
            if (dq % 2)
            {
                continue;
            }
            n++;
        }
    }
    return n;
}

void init_row(ROW *row, size_t n, char *data)
{
    row->data = data;
    row->row_n = n;
    row->n_cell = n_cell(row);
    row->cells = (CELL *)malloc(sizeof(CELL) * row->n_cell);
    load_cell(row);
    return;
}

char *parse_row(CSV *csv, char **save)
{
    char *buff = malloc(ROW_SIZE * sizeof(char));

    char *b = buff;
    char *c = *save ? *save : csv->data;
    int dq = 0;
    for (; *c; c++, b++)
    {
        *b = *c;
        if (*c == '"')
        {
            dq++;
        }
        if (*c == '\n')
        {
            if (dq % 2)
            {
                continue;
            }
            *b = '\0';
            *save = c + 1;
            return buff;
        }
    }
    free(buff);
    return NULL;
}

void load_rows(CSV *csv)
{
    ROW *row = csv->rows;
    ROW *end = row + csv->n_row;
    char *save = NULL;
    for (size_t n = 0; row < end; row++, n++)
    {
        char *data = parse_row(csv, &save);
        if (!data)
            return;
        // printf("load row %i...\n", n);
        init_row(row, n, data);
    }
    return;
}

void print_rows(CSV *csv)
{
    ROW *row = csv->rows;
    ROW *end = row + csv->n_row;

    for (; row < end; row++)
    {
        puts(row->data);
    }
    return;
}

void print_csv(CSV *csv)
{
    printf("filename: %s\ndata: %p\nn_row: %zu\nrows %p\n", csv->filename, csv->data, csv->n_row, csv->rows);
    print_rows(csv);
    return;
}

void init_csv(CSV *csv, char *fn)
{
    char *data = read_csv(fn);
    csv->filename = fn;
    csv->data = data;
    csv->n_row = n_row(csv);
    csv->rows = (ROW *)malloc(sizeof(ROW) * csv->n_row);
    load_rows(csv);
    return;
}

char *read_csv(const char *fn)
{
    FILE *f = open_csv(fn, "r");
    if (!f)
    {
        puts("open csv failed.\n");
        return NULL;
    }
    // printf("%s opened.", fn);
    size_t fs = file_size(f);
    char *fc = (char *)malloc(fs * sizeof(char));
    if (!fc)
    {
        puts("malloc failed.\n");
        return NULL;
    }
    fread(fc, fs, 1, f);
    // printf("%s content loaded to memory.", fn);
    fclose(f);
    // printf("%s closed.", fn);
    return fc;
}

FILE *open_csv(const char *fn, char *mode)
{
    return (!is_csv(fn)) ? NULL : fopen(fn, mode);
}

size_t file_size(FILE *f)
{
    fseek(f, 0, SEEK_END);
    size_t size = ftell(f);
    fseek(f, 0, SEEK_SET);
    return size;
}

size_t is_csv(const char *fn)
{
    return my_strcmp(file_ext(fn), ".csv") ? 0 : 1; // it could be UPPERCASE: .CSV
}

char *file_ext(const char *fn)
{
    for (; *fn; fn++)
    {
        if (*fn == '.') // last 3 dight csv , strrchr
            return (char *)fn;
    }
    return NULL;
}

int my_strcmp(const char *str1, const char *str2)
{
    for (; *str1; str1++, str2++)
    {
        if (*str1 != *str2)
            break;
    }
    return *(unsigned char *)str1 - *(unsigned char *)str2;
}

void free_cells(ROW *row)
{
    CELL *cell = row->cells;
    CELL *end = cell + row->n_cell;
    size_t row_n = row->row_n;

    for (int cell_n = 0; cell < end; cell++, cell_n++)
    {
        // printf("cell: %zu%i freed.\n", row_n, cell_n);
        free(cell->data);
    }
    free(row->cells);
    // printf("all cells in row %zu freed.\n", row->row_n);
}

void free_rows(CSV *csv)
{
    ROW *row = csv->rows;
    ROW *end = row + csv->n_row;

    for (int roll_n = 0; row < end; row++, roll_n++)
    {
        free_cells(row); //free_cell
        // printf("row %i freed.\n", roll_n);
        free(row->data);
    }
    free(csv->rows);
    // printf("all rows freed.\n");
}

void free_csv(CSV *csv)
{
    free(csv->data);
    free_rows(csv); // free_row
    puts("all memory freed.\n");
    return;
}

ROW *get_row(CSV *csv, size_t r)
{
    size_t n_row = csv->n_row;
    if (r >= n_row)
    {
        printf("warning: row range: 0 ~ %zu", n_row - 1);
        return NULL;
    }
    ROW *row = csv->rows;
    return row + r;
}

CELL* get_row_cell(ROW* row, size_t c){
    if (!row) {
        printf("warning: ROW* is null.\n");
        return NULL;
    }
    size_t n_cell = row->n_cell;
    if (c >= n_cell) {
        printf("warning: row range: 0 ~ %zu\n", n_cell - 1);
        return NULL;
    }

    return row->cells + c;
}

CELL *get_cell(CSV *csv, size_t r, size_t c)
{
    ROW *row = get_row(csv, r);
    
    size_t n_cell = row->n_cell;
    if (c >= n_cell)
    {
        printf("warning: cell range: 0 ~ %zu", n_cell - 1);
        return NULL;
    }
    CELL *cell = row->cells;
    return cell + c;
}

char *trim(char *str)
{
    char *s = str;

    for (char *s = str; *s; s++)
    {
        if (*s != ' ')
        {
            break;
        }
    }
    return s;
}

char *nextchr(char *str, char ch)
{
    int c = 0;
    for (char *s = str; *s; s++)
    {
        if (*s == ch)
        {
            c++;
        }
        if (c == 2)
        {
            return s;
        }
    }
    return str;
}

void debug_print(CSV *csv)
{

    for (size_t r = 0; r < csv->n_row; r++)
    {
        ROW *row = get_row(csv, r);
        if (!row) {
            fprintf(stderr, "*row %zu is NULL;", r);
            return;
        }
        // printf("row%i: %s", r, row->data);
        for (size_t c = 0; c < row->n_cell; c++)
        {
            CELL *cell = get_cell(csv, r, c);
            if (!cell) {
                fprintf(stderr, "*cell %zu is NULL", c);
                return;
            }
            // printf("cell%i%i: %s ", r, c, cell->data);
            printf("%s ", cell->data);
        }
        printf("\n");
    }
}