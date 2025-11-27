#!/bin/bash

set -x

rm -f get_line_from_file.o
rm -f test_get_line_from_file.out

gcc -c -Wall -Werror -Wextra -Wundef -Wunreachable-code -Winit-self -Wparentheses -Wconversion -Wsign-conversion -Wsign-compare -Werror-implicit-function-declaration -Wmissing-prototypes -Wmissing-declarations -Wno-unused-parameter -Wformat-security get_line_from_file.c

if [ "$?" -ne "0" ]; then
    exit;
fi

rm -f get_line_from_file.o

gcc -Wall -Werror -Wextra -Wundef -Wunreachable-code -Winit-self -Wparentheses -Wconversion -Wsign-conversion -Wsign-compare -Werror-implicit-function-declaration -Wmissing-prototypes -Wmissing-declarations -Wno-unused-parameter -Wformat-security get_line_from_file.c test_get_line_from_file.c -o test_get_line_from_file.out

