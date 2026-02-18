#define _XOPEN_SOURCE 700
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char *items;
  size_t count;
  size_t capacity;
} Dynamicarray;

int main(int argc, char *argv[]) {
  setlocale(LC_ALL, "");

  printf("%s\n", setlocale(LC_COLLATE, NULL));

  // Dynamicarray sortedwords = {0};

  if (argc < 2 || argc > 7) {
    printf("Usage: Must be between 1 and 6 arguments");
    return EXIT_FAILURE;
  }

  char *s1 = argv[1];
  char *s2 = argv[2];

  int numcomp = strcoll(s1, s2);

  if (numcomp < 0) {
    printf("First word: %s\n", s1);
  } else {
    printf("First word: %s\n", s2);
  }

  return EXIT_SUCCESS;
}
