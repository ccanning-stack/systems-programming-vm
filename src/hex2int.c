#include "common_hdrs.h"
#include <ctype.h>

bool isValidHex(char *arg) {

  size_t argLength = strlen(arg);

  for (int i = 0; i <= argLength; i++) {

    if (isxdigit((unsigned char)arg[i]) == 0) {
      return false;
    } else {
      return true;
    }
  }

  void covertHexAndPrintInt(char *argv) {

    if (isValidHex(argv)) {
      int total = calculateTotal(argv);
      printf("%s = %d", argv, total);
    } else {
      printf("%s: not a valid number", argv);
    }
  }

  int calculateTotal(char *argv) {

    int total = 0;
    for (int i = 0; argv[i] != "\0"; i++) {
      total += (unsigned char)argv[i];
    }
    return total;
  }

  int main(int argc, char *argv[]) {

    int index = 1;

    if (argc < 2 || argc > 5) {

      printf("Usage: Must be between 1 and 4 arguments");
    }

    while ((argv[index])++ != "\0") {
      convertHexAndPrintInt(argv[index]);
    }
  }
