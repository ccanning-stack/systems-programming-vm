#define _GNU_SOURCE
#include "../common/common_hdrs.h"
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

#define DEFAULT_BUFFER_SIZE 4096

#define PERMISSIONS (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH)

int main(int argc, char *argv[]) {
  int source_fd;
  ssize_t num_bytes_read;
  ssize_t num_bytes_written_stdout;
  char message[512];

  int buffer_size = DEFAULT_BUFFER_SIZE;
  char *buffer = NULL;

  int opt;

  while ((opt = getopt(argc, argv, ":B:")) != -1) {
    switch (opt) {
    case 'B': {
      char *end;
      long val = strtol(optarg, &end, 10);

      if (*end != '\0' || val <= 0) {
        usage_error("invalid buffer size");
      }

      buffer_size = (int)val;
      break;
    }

    case ':':
      usage_error("missing argument for -B");

    case '?':
      usage_error("invalid option");
    }
  }

  if (argc - optind > 10) {
    usage_error("max number of args permitted: 10");
  }

  buffer = malloc(buffer_size);
  if (buffer == NULL) {
    fatal_error(errno, "malloc failed");
  }

  while (optind < argc) {

    source_fd = open(argv[optind], O_RDONLY);

    if (source_fd == -1) {
      free(buffer);
      fatal_error(errno, "unable to open target for reading");
    }

    num_bytes_read = read(source_fd, buffer, buffer_size);

    if (num_bytes_read == 0) {
      break;
    }

    if (num_bytes_read == -1) {
      free(buffer);
      fatal_error(errno, "read error");
    }

    ssize_t total_written = 0;

    while (total_written < num_bytes_read) {
      num_bytes_written_stdout = write(STDOUT_FILENO, buffer + total_written,
                                       num_bytes_read - total_written);

      if (num_bytes_written_stdout == -1) {
        fatal_error(errno, "stdout write error");
      }
      total_written += num_bytes_written_stdout;
    }

    if (close(source_fd) == -1) {
      sprintf(message, "error closing source file %s", argv[optind]);
      fatal_error(errno, message);
    }

    optind++;
  }

  free(buffer);

  return 0;
}
