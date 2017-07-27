#!/bin/bash

echo compile
gcc -O2 -Wall kthstat.c grader.c -o sol.exe || exit

for f in `ls ??` ; do
  echo test $f
  ./sol.exe < $f > $f.r
done
