#!/bin/bash

echo Compile validator...
g++ -O2 -x c++ -I. validate.cpp -o validate.exe || exit

echo Validating tests...

for t in `ls ../tests/??` ; do
	echo -n "validate "
	./validate.exe <$t || exit
done
