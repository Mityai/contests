#!/bin/bash

function compile 
{
  echo "Compile $1"
  if ! [ -e $1.exe ] ; then
    g++ -O2 -Wall $1.cpp -o $1.exe || exit
  else
    echo "  nothing to do"
  fi
}

nt=1
base=23917

echo "Clean workspace"
#bash wipeall.sh tests

echo "Generate tests"
compile gen_tests

./gen_tests.exe

echo "Validate tests"
bash validate.sh || exit

echo "Generate answers"
bash gen_ans_cpp.sh || exit

testdir=../tests
echo "Move tests to $testdir"
rm -f -r $testdir
mkdir $testdir || exit
mv ?? $testdir/ || exit
mv ??.a $testdir/ || exit
