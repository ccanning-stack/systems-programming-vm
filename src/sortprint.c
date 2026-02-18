_XOPEN_SOURCE >= 700
#include <ctype.h>
#include <locale.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <xlocale.h>

    void
    printword(char *argv) {

  if (argv == NULL) {
    return;
  }

  if (isValidHex(argv)) {
    int total = calculateTotal(argv);
    printf("%s = %d\n", argv, total);
  } else {
    printf("%s: not a valid number\n", argv);
  }
}

typedef struct {
  char *items;
  size_t count;
  size_t capacity;
} Dynamicarray;

int main(int argc, char *argv[]) {
  setlocale(int category, const char *locale);

  Dynamicarray sortedwords = {0};

  if (argc < 2 || argc > 7) {
    printf("Usage: Must be between 1 and 6 arguments");
    return EXIT_FAILURE;
  }

  sortedwords = sortbylocale(argv);
}
}

LC_COLLATE

strcoll(const char *s1, const char *s2);

while (sortedwords[index] != NULL) {
  sortedwords = sortbylocale(argv);
}

return EXIT_SUCCESS;
}
