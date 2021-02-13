#define  _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LogError(...) fprintf(stderr, __VA_ARGS__)

typedef struct {
	char* data;
} Cell;

void Cell_Init(Cell* cell) {
	cell->data = NULL;
}

void Cell_Release(Cell* cell) {
	if (cell->data) {
		free(cell->data);
		cell->data = NULL;
	}
}

//-------------------

#define Row_MaxCell 128

typedef struct {
	Cell cells[Row_MaxCell];
	size_t cellCount;
} Row;

void Row_Init(Row* row) {
	row->cellCount = 0;
}

void Row_Release(Row* row) {
	Cell* p = row->cells;
	Cell* end = p + row->cellCount;
	for (; p < end; p++) {
		Cell_Release(p);
	}
	row->cellCount = 0;
}

int Row_AddCell(Row* row, char* data) {
	if (row->cellCount >= Row_MaxCell) {
		LogError("reach max cell count");
		return -1;
	}

	Cell* cell = &row->cells[row->cellCount];
	Cell_Init(cell);
	cell->data = strdup(data);
	row->cellCount++;

	return 0;
}

void Row_Print(Row* row) {
	Cell* c = row->cells;
	Cell* end = c + row->cellCount;
	for (; c < end; c++) {
		printf("[%s]", c->data);
	}
	printf("\n");
}

//----------------------

#define Parser_BufSize 512

typedef struct {
	char* filename;
	char* data;
	size_t dataSize;
	char* cur;
	char* end;
} Parser;

void Parser_Init(Parser* p) {
	p->filename = NULL;
	p->data = NULL;
	p->dataSize = 0;
	p->cur = NULL;
	p->end = NULL;
}

void Parser_Release(Parser* p) {
	if (p->filename) {
		free(p->filename);
		p->filename = NULL;
	}

	if (p->data) {
		free(p->data);
		p->data = NULL;
		p->dataSize = 0;
	}

	p->cur = NULL;
	p->end = NULL;
}

int Parser_Open(Parser* p, const char* filename) {
	Parser_Release(p);
	p->filename = strdup(filename);

	int ret = -1;
	char* data = NULL;
	FILE* file = NULL;

	file = fopen(filename, "rb");
	if (!file) {
		LogError("cannot open file %s\n", filename);
		ret = -1;
		goto cleanup;
	}

	fseek(file, 0, SEEK_END);
	size_t dataSize = ftell(file);
	fseek(file, 0, SEEK_SET);

	data = (char*)malloc(dataSize + 1);
	if (!data) {
		LogError("error allocate memory\n");
		ret = -2;
		goto cleanup;
	}

	if (1 != fread(data, dataSize, 1, file)) {
		LogError("error fread\n");
		ret = -3;
		goto cleanup;
	}

	data[dataSize] = 0;

	p->cur = data;
	p->end = data + dataSize;

	p->data = data;
	p->dataSize = dataSize;
	return 0;

cleanup:
	if (data) {
		free(data);
	}

	if (file) {
		fclose(file);
	}
	return ret;
}

int Parser_NextCell(Parser* p, Row* row) {
	// trim space
	for (;p->cur < p->end; p->cur++) {
		if (*p->cur != ' ')
			break;
	}

	char buf[Parser_BufSize + 1];
	char* b = buf;

	int nextRow = 0;
	int insideQuote = 0;

	while (p->cur < p->end) {
		char ch = *p->cur;

		if (insideQuote) {
			if (ch == '"') {
				p->cur++;
				if (p->cur >= p->end) break;
					
				ch = *p->cur;
				if (ch == '"') {
					*b++ = ch;
					p->cur++;
					continue;
				}

				insideQuote = 0;
				continue;
			}
		} else {
			if (ch == '"') {
				p->cur++;
				insideQuote = 1;
				continue;
			}

			if (ch == ',') {
				p->cur++;
				break;
			}

			if (ch == '\n' || ch == '\r') {
				p->cur++;
				if (p->cur < p->end && ch == '\r' && *p->cur == '\n')
					p->cur++;

				nextRow = 1;
				break;
			}
		}

		// success read 1 char
		if (b - buf >= Parser_BufSize) {
			LogError("cell size excess buf size");
			return -1;
		}

		*b++ = ch;
		p->cur++;
	}

	if (insideQuote) {
		LogError("End of file within quote");
		return -2;
	}

	if (b == buf)
		return 0;

	*b = 0;
	Row_AddCell(row, buf);

	return nextRow;
}

// ret < 0: error, 0: no data, 1: has data
int Parser_NextRow(Parser* p, Row* row) {
	Row_Release(row);
	Row_Init(row);

	if (!p->cur) return -1;

	// trim space
	for (;p->cur < p->end; p->cur++) {
		if (*p->cur != ' ')
			break;
	}

	for (;;) {
		if (p->cur >= p->end) return 0;

		int ret = Parser_NextCell(p, row);
		if (ret < 0) return ret; // error
		if (ret == 1) break; // next row
	}
	return 1; // has data
}

//---------------------------

int main() {
	Parser parser;
	Parser_Init(&parser);

	if (Parser_Open(&parser, "test.csv")) {
		return -1;
	}

	Row row;
	Row_Init(&row);

	while (Parser_NextRow(&parser, &row) > 0) {
		Row_Print(&row);
	}

	Row_Release(&row);

	Parser_Release(&parser);
	return 0;
}