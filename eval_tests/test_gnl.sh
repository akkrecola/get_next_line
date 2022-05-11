#!/bin/bash

echo '>>>>>>> Running norminette for C files and header. <<<<<<<'
norminette ../get_next_line.c ../get_next_line.h

echo
if [[ $# != 1 ]]; then
	echo 'Usage: give the filename of the file to read as parameter'
	exit
fi

echo ***
echo ***
echo ***

make debug && make clean
if [[ $OSTYPE == "darwin18.0" ]]; then
	echo '>>>>>> Running leaks test. <<<<<<<'
	leaks -atExit -- ./gnl.out test_files/$1 && make fclean
elif [[ $OSTYPE == "linux-gnu" ]]; then
	echo '>>>>>>> Running valgrind. <<<<<<<'
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ./gnl.out test_files/$1
else
	echo 'Operating system not reacognized, skipping memcheck.'
fi

echo
echo ***
echo ***
echo ***

echo
echo '>>>>>>> Running tests with -fsanitize=address flag. <<<<<<<<'
make fclean && make sanitize && ./gnl.out test_files/$1
echo
echo ***
echo ***
echo ***

echo 'Tests completed, read the output at the resulting file output'
