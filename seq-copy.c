#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <errno.h>

static uintmax_t parse(const char *arg, const char *name) {
    errno = 0;
    char *end;
    uintmax_t value = strtoumax(arg, &end, 10);
    if (end == arg) {
        fprintf(stderr, "error: no digits found in %s\n", name);
        exit(EXIT_FAILURE);
    }
    if (*end != '\0') {
        fprintf(stderr, "error: invalid trailing characters in %s: %s\n", name, end);
        exit(EXIT_FAILURE);
    }
    if (errno == ERANGE) {
        fprintf(stderr, "error: %s out of range\n", name);
        exit(EXIT_FAILURE);
    }
    return value;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "usage: command number1 number2\n");
        exit(EXIT_FAILURE);
    }

    uintmax_t num1 = parse(argv[1], "number1");
    uintmax_t num2 = parse(argv[2], "number2");

    if (num1 >= num2) {
        fprintf(stderr, "error: number1 (%" PRIuMAX ") must be smaller than number2 (%" PRIuMAX ")\n", num1, num2);
        exit(EXIT_FAILURE);
    }

    while (num1 <= num2) {
        printf("%" PRIuMAX "\n", num1++);
    }

    return EXIT_SUCCESS;
}
