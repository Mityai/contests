#!/bin/bash

echo compile
g++ -O2 -Wall kthstat.cpp grader.cpp -o sol.exe || exit

for f in `ls ??` ; do
  echo test $f
  ./sol.exe < $f > $f.a
done
