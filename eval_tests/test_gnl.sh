#!/bin/bash

make re && make clean && valgrind --leak-check=full --track-origins=yes ./gnl.out test_files/eutreaty >> output
