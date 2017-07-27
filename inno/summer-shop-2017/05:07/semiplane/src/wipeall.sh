#!/bin/bash

testdir=../tests/

if [[ $1 == "tests" ]] ; then
  echo "Delete directory with tests"
  rm -f -r $testdir
fi

echo "Delete some files"
rm *.class *.o *.obj *.exe *.in *.out *.txt out 2> /dev/nul
rm ?? ??.a ??? ???.a 2> /dev/nul
