#define _GNU_SOURCE
#include "../common/common_hdrs.h"
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <libgen.h>
#include <sys/stat.h>

#define DEFAULT_BUFFER_SIZE 4096

#define PERMISSIONS \
    (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH)

int main(int argc, char *argv[])
{
    int source_fd;
    int target_fd;
    ssize_t num_bytes_read;
    ssize_t num_bytes_written;

    mode_t permissions = PERMISSIONS;
    char message[512];

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

    if (argc - optind != 2) {
        sprintf(message, "%s source destination", basename(argv[0]));
        usage_error(message);
    }

    buffer = malloc(buffer_size);
    if (buffer == NULL) {
        fatal_error(errno, "malloc failed");
    }

    source_fd = open(argv[optind], O_RDONLY);
    if (source_fd == -1) {
        sprintf(message, "unable to open %s for reading", argv[optind]);
        fatal_error(errno, message);
    }

    target_fd = open(argv[optind + 1],
                     O_WRONLY | O_CREAT | O_TRUNC,
                     permissions);

    if (target_fd == -1) {
        sprintf(message, "unable to open %s for writing", argv[optind + 1]);
        fatal_error(errno, message);
    }

    while ((num_bytes_read = read(source_fd, buffer, buffer_size)) > 0) {
        num_bytes_written = write(target_fd, buffer, num_bytes_read);

        if (num_bytes_written == -1) {
            fatal_error(errno, "write error");
        }

        if (num_bytes_written != num_bytes_read) {
            fatal_error(-1, "partial write error");
        }
    }

    if (num_bytes_read == -1) {
        fatal_error(errno, "read error");
    }

    if (close(source_fd) == -1) {
        sprintf(message, "error closing source file %s", argv[optind]);
        fatal_error(errno, message);
    }

    if (fsync(target_fd) == -1) {
        fatal_error(errno, "fsync error");
    }

    if (close(target_fd) == -1) {
        sprintf(message, "error closing target file %s", argv[optind + 1]);
        fatal_error(errno, "error closing target file");
    }

    free(buffer);

    return 0;
}
