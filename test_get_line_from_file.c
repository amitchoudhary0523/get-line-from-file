
/*
 * License:
 *
 * This file has been released under "unlicense" license
 * (https://unlicense.org).
 *
 * This is free and unencumbered software released into the public domain.
 *
 * Anyone is free to copy, modify, publish, use, compile, sell, or distribute
 * this software, either in source code form or as a compiled binary, for any
 * purpose, commercial or non-commercial, and by any means.
 *
 * For more information about this license, please visit - https://unlicense.org
 */

/*
 * Author: Amit Choudhary
 * Email: amitchoudhary0523 AT gmail DOT com
 */

#include "get_line_from_file.h"

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{

    int fd = -1;
    char *line = NULL;
    int error_num = 0;

    if (argc != 2) {
        printf("\n");
        printf("Error: Incorrect usage.\n");
        printf("\n");
        printf("This program takes only one argument which is the name of a"
               " file whose contents have to be printed.\n");
        printf("\n");
        printf("Usage: %s file_name\n", argv[0]);
        printf("\n");
        printf("Please try again. Exiting..\n");
        printf("\n");
        exit(1);
    }

    fd = open(argv[1], O_RDONLY);

    if (fd < 0) {
        printf("\n%s: File \"%s\" could not be opened. Exiting..\n\n",
               __FILE__, argv[1]);
        exit(1);
    }

    while ((line = get_line_from_file(fd, &error_num)) != NULL) {
        printf("%s\n", line);
        free(line);
    }

    if (error_num != 0) {
        printf("\nError number returned = %d\n\n", error_num);
    }

    close(fd);

} // end of function main()

