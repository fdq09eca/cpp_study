#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define TEST(EXPR)                                                              \
  do                                                                            \
  {                                                                             \
    printf("[%s] Line %3d: %s\n", ((EXPR) ? " OK " : "FAIL"), __LINE__, #EXPR); \
  } while (0) //========

size_t g_malloc_count = 0;

void *my_malloc(size_t n)
{
  g_malloc_count++;
  return malloc(n);
}

void my_free(void *p)
{
  g_malloc_count--;
  free(p);
}

//=========

#if _DEBUG
#define debug_print(...) printf(__VA_ARGS__)
#else
#define debug_print(...)
#endif

//=========

// insert
// find
// print
