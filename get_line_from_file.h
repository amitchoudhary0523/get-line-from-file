
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

#ifndef _GET_LINE_FROM_FILE_H_
#define _GET_LINE_FROM_FILE_H_

#define NO_ERROR 0 // no error happened.
#define INVALID_FD -1 // fd is less than 0.
#define NO_MEMORY -2 // memory not available.
#define FILE_LSEEK_ERROR -3 // error in seeking file

/*
 * get_line_from_file():
 *
 * Function get_line_from_file() is an alternate implementation of C standard
 * library's getline() function and this function is much simpler to use than
 * getline().
 *
 * Function get_line_from_file() returns a line from the file represented by fd.
 *
 * This function supports only regular files (no pipes, sockets, etc).
 *
 * If fd is less than 0 then NULL is returned and *error_num is assigned the
 * appropriate error value (INVALID_FD in this case).
 *
 * In case of any error, *error_num is assigned the appropriate error value.
 *
 * The high level algorithm of this function is:
 *
 *      The function get_line_from_file() reads some bytes in a buffer from the
 *      file and tries to find the newline in the buffer. If the newline is not
 *      found then it reads more bytes from the file in the buffer. When the
 *      newline is found in the buffer, then the newline is replaced with the
 *      null terminating character and the buffer is reallocated to the correct
 *      size. Then the file offset for reading is set to the start of the next
 *      line. And then the buffer is returned to the user.
 *
 * Please note that the returned line/buffer doesn't contain any newlines.
 *
 * The line/buffer returned by this function is allocated using realloc(),
 * so it is user's responsibility to free the line (free memory).
 */
char *get_line_from_file(int fd, int *error_num);

#endif

