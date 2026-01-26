#include "common_hdrs.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int calculateTotal(char *argv) {

  int total = 0;

  for (int i = 2; argv[i] != '\0'; i++) {
    unsigned char c = (unsigned char)argv[i];
    int v;

    if (c >= '0' && c <= '9')
      v = c - '0';
    else if (c >= 'a' && c <= 'f')
      v = c - 'a' + 10;
    else
      v = c - 'A' + 10;

    total = total * 16 + v;
  }

  return total;
}

bool isValidHex(char *arg) {

  size_t argLength = strlen(arg);

  if (arg[0] == '0' && arg[1] == 'x' && argLength >= 3) {
    for (unsigned i = 2; i < argLength; i++) {

      if (isxdigit((unsigned char)arg[i]) == 0) {
        return false;
      } else {
        return true;
      }
    }
  }
  return false;
}

void convertHexAndPrintInt(char *argv) {

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

int main(int argc, char *argv[]) {

  int index = 1;

  if (argc < 2 || argc > 5) {

    printf("Usage: Must be between 1 and 4 arguments");
    return EXIT_FAILURE;
  }

  while (argv[index] != NULL) {
    convertHexAndPrintInt(argv[index]);
    index++;
  }

  return EXIT_SUCCESS;
}
