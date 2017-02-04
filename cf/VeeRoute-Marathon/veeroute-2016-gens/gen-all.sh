#!/bin/bash
g++ -std=c++11 -O2 -Wall -Wextra -Wconversion -static -o gen gen.cpp

./gen 1 > 01
./gen 2 > 02
./gen 3 > 03
./gen 4 > 04
./gen 5 > 05
./gen 6 > 06
./gen 7 > 07
./gen 8 > 08
./gen 90 > 9
./gen 10 > 10
