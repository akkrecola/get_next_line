#!/bin/bash

make re && make clean && leaks -atExit -- ./gnl.out test_files/eutreaty >> output
