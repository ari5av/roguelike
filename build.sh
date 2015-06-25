#!/bin/bash

for file in *.c
do
  gcc -c -o $file.o $file
done

g++ -o roguelike *.o -lm -lpanel -lncurses && rm *.o
