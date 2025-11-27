
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

#include <stddef.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>

#define NEW_LINE '\n'

#define BUF_SIZE_INCREMENT 1024

char *get_line_from_file(int fd, int *error_num)
{

    char *buf = NULL;
    char *buf_temp = NULL;

    long curr_buf_size = 0;
    long curr_data_len = 0;

    ssize_t bytes_read = -1;
    int end_of_file_reached_or_error = 0;
    int new_line_found = 0;
    long i = 0;

    *error_num = NO_ERROR;

    if (fd < 0) {
        *error_num = INVALID_FD;
        return NULL;
    }

    while (1) {

        buf_temp = buf;

        buf = realloc(buf, (size_t)(curr_buf_size + BUF_SIZE_INCREMENT));

        if (!buf) {
            free(buf_temp);
            *error_num = NO_MEMORY;
            return NULL;
        }

        curr_buf_size = curr_buf_size + BUF_SIZE_INCREMENT;

        // read data from file
        while (curr_data_len != curr_buf_size) {

            bytes_read = read(fd, buf + curr_data_len,
                              (size_t)(curr_buf_size - curr_data_len));

            if (bytes_read == 0) { // end of file reached
                // Check if no bytes were read earlier also in this call to
                // get_line_from_file(). If yes, then this means that end of
                // test file was reached (but not actually read) in the last
                // call to get_line_from_file(). So, this time end of file was
                // read and 0 was returned by read. So, since there are no bytes
                // to process, free the buffer and return NULL.
                if (curr_data_len == 0) {
                    free(buf);
                    return NULL;
                }
            } // end of if bytes_read == 0

            if (bytes_read <= 0) {
                end_of_file_reached_or_error = 1;
                break;
            } // end of if bytes_read <= 0

            curr_data_len = curr_data_len + bytes_read;

        } // end of inner while (1) loop

        new_line_found = 0;

        for (i = 0; i < curr_data_len; i++) {
            if (buf[i] == NEW_LINE) {
                buf[i] = 0;
                new_line_found = 1;
                break;
            }
        } // end of for loop

        if (new_line_found) {

            // realloc and seek
            buf_temp = buf;

            buf = realloc(buf, (size_t)(i + 1));

            if (!buf) {
                free(buf_temp);
                *error_num = NO_MEMORY;
                return NULL;
            }

            if (lseek(fd, (i + 1) - curr_data_len, SEEK_CUR) < 0) {
                *error_num = FILE_LSEEK_ERROR;
                free(buf);
                return NULL;
            }

            return buf;

        } else { // new line not found

            // NEW_LINE not found and end of file has been reached or some
            // error happened. So, allocate one extra byte for terminating
            // null byte and return.
            if (end_of_file_reached_or_error) {

                buf_temp = buf;

                buf = realloc(buf, (size_t)(curr_data_len + 1));

                if (!buf) {
                    free(buf_temp);
                    *error_num = NO_MEMORY;
                    return NULL;
                }

                buf[curr_data_len] = 0;

                return buf;

            } // end of if end_of_file_reached_or_error

        } // end of if - else (new_line_found)

    } // end of outer while (1) loop

} // end of get_line_from_file

