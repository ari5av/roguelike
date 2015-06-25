#!/bin/bash

for file in *.c
do
  gcc -c -o $file.o $file
done

g++ -o keyboard_codes_test *.o -lm -lpanel -lncurses && rm *.o
