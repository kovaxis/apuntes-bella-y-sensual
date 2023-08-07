#!/bin/bash

OK=0

if [ "$1.cpp" -nt tmp ] || [ "$2" = "f" ]
then
    echo "compiling..." >&2
    g++ -g -std=c++17 -o tmp "$1.cpp"
    OK=$?
fi

ulimit -s 1000000
(exit $OK) && echo "running..." >&2 && valgrind -q ./tmp
