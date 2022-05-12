#!/bin/bash

clear
echo '>>>>> Running norminette for C files and header.'
norminette ../get_next_line.c ../get_next_line.h
if [[ $# != 1 ]]; then
	echo 'Usage: give the filename of the file to read as parameter'
	exit
fi

source rename.sh c > /dev/null

make fclean > /dev/null && make debug > /dev/null
# For some reason, the school Mac $OSTYPE is not recognized so it's just in the
# else statement now.
#if [[ $OSTYPE == "darwin18.0" ]]; then
	#echo '>>>>> Running leaks test. <<<<<'
	#leaks -atExit -- ./gnl.out test_files/$1 && make fclean
echo
if [[ $OSTYPE == "linux-gnu" ]]; then
	echo '>>>>> Running valgrind.'
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ./gnl.out test_files/$1
else
	echo '>>>>> Running leaks test.'
	leaks -atExit -- ./gnl.out test_files/$1
	#echo 'Operating system not recognized, skipping memcheck.'
fi
echo
echo '>>>>> Running tests with -fsanitize=address flag. (No output == working)'
make fclean > /dev/null && make sanitize > /dev/null
./gnl.out test_files/$1
make clean > /dev/null
echo '>>><<<'
echo '>>>>> Tests completed, read the output at the resulting file output.'
