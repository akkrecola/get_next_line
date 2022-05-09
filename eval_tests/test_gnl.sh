#!/bin/bash

echo 'Running norminette for C files and header.'
norminette ../get_next_line.c ../get_next_line.h

echo ***
echo ***
echo ***

echo 'Running leaks test.'
make fclean && make debug && make clean && leaks -atExit -- ./gnl.out test_files/$1 && make fclean

echo ***
echo ***
echo ***

echo 'Running tests with -fsanitize=address flag.'
make sanitize && ./gnl.out test_files/$1 && make fclean

echo
echo ***
echo ***
echo ***
echo

echo 'Tests completed, read the output at the resulting file output'
