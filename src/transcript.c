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
  int target_fd;
  ssize_t num_bytes_read;
  ssize_t num_bytes_written_stdout;
  ssize_t num_bytes_written_file;

  int buffer_size = DEFAULT_BUFFER_SIZE;
  void *buffer = NULL;

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

  if (argc - optind != 1) {
    usage_error("missing output file");
  }

  buffer = malloc(buffer_size);
  if (buffer == NULL) {
    fatal_error(errno, "malloc failed");
  }

  target_fd = open(argv[optind], O_WRONLY | O_CREAT | O_TRUNC, PERMISSIONS);

  if (target_fd == -1) {
    fatal_error(errno, "unable to open target for writing");
  }

  while ((num_bytes_read = read(STDIN_FILENO, buffer, buffer_size)) > 0) {

    num_bytes_written_stdout = write(STDOUT_FILENO, buffer, num_bytes_read);

    if (num_bytes_written_stdout == -1) {
      fatal_error(errno, "stdout write error");
    }

    num_bytes_written_file = write(target_fd, buffer, num_bytes_read);

    if (num_bytes_written_file == -1) {
      fatal_error(errno, "file write error");
    }

    if (num_bytes_written_stdout != num_bytes_read ||
        num_bytes_written_file != num_bytes_read) {
      fatal_error(-1, "partial write error");
    }
  }

  if (num_bytes_read == -1) {
    fatal_error(errno, "read error");
  }

  if (close(target_fd) == -1) {
    fatal_error(errno, "error closing target file");
  }

  free(buffer);

  return 0;
}
