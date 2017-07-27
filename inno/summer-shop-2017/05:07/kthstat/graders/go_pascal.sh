#!/bin/bash

echo compile
fpc grader.pas -osol.exe || exit

for f in `ls ??` ; do
  echo test $f
  ./sol < $f > $f.r
done
