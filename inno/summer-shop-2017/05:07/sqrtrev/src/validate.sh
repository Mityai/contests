#!/bin/bash

if ! [ -e validate.exe ] ; then
  echo "Compile validator"
  g++ -O2 -Wall validate.cpp -o validate.exe || exit
fi

for i in `ls ??` ; do
  echo "[$i]"
  ./validate.exe < $i || exit
done
echo " Good! =)"

