#include "common_hdrs.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

int calculateTotal(char *argv) {

  int total = 0;

  for (int i = 2; argv[i] != '\0'; i++) {
    total += (unsigned char)argv[i];
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

  if (isValidHex(argv)) {
    int total = calculateTotal(argv);
    printf("%s = %d", argv, total);
  } else {
    printf("%s: not a valid number", argv);
  }
}

int main(int argc, char *argv[]) {

  int index = 1;

  if (argc < 2 || argc > 5) {

    printf("Usage: Must be between 1 and 4 arguments");
  }

  while ((argv[index])++ != NULL) {
    convertHexAndPrintInt(argv[index]);
  }
}
