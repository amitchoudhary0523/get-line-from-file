
File "get_line_from_file.c" implements a function get_line_from_file() which is
an alternate implementation of C standard library's getline() function and this
function (get_line_from_file()) is much simpler to use than getline().

The signature of this function is:

    char *get_line_from_file(int fd, int *error_num);

So, this function returns a line from the file represented by 'fd'. Subsequent
calls to this function will return subsequent lines from the file.

---- End of README ----
