#define _XOPEN_SOURCE 700
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  const char **items;
  size_t count;
  size_t capacity;
} Words;

#define da_append(da, elem)                                                    \
  do {                                                                         \
    if (da.count >= da.capacity) {                                             \
      if (da.capacity == 0) {                                                  \
        da.capacity = 256;                                                     \
      } else {                                                                 \
        da.capacity *= 2;                                                      \
      }                                                                        \
      da.items = realloc(da.items, da.capacity * sizeof(*da.items));           \
    }                                                                          \
    da.items[da.count++] = elem;                                               \
  } while (0)

int cmp_strcoll(const void *a, const void *b) {
  const char *const *sa = a;
  const char *const *sb = b;

  return strcoll(*sa, *sb);
}

int main(int argc, char *argv[]) {
  setlocale(LC_ALL, "");

  Words words = {0};

  if (argc < 2 || argc > 7) {
    printf("Usage: Must be between 1 and 6 arguments");
    return EXIT_FAILURE;
  }

  for (int i = 1; i <= argc; i++) {
    da_append(words, argv[i]);
  }

  qsort(words.items, words.count, sizeof(*words.items), cmp_strcoll);

  while (words.count > 0) {
    printf("%s\n", words.items[words.count]);
  }
  return EXIT_SUCCESS;
}
