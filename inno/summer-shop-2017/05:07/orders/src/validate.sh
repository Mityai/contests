#!/bin/bash

function fail
{
  echo "Validation fail!"
  exit 1
}

echo "Compile validator"

make validate.exe

for i in `ls ../tests/??` ; do
  echo "[$i]"
  ./validate.exe < $i || fail
done
echo " Good! =)"

rm validate || rm validate.exe
