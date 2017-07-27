#!/bin/bash

echo "Generate answers"

prob=semiplane
sol=../sols/semiplane_sk_nsqrtn

echo "problem = $prob"
echo "solution = $sol"

if ! [ -e sol.exe ] ; then
  echo "Compile solution"
  g++ -O2 -Wall $sol.cpp -o sol.exe || exit
fi

for i in `ls ??` ; do
  echo "Test $i"
  cp $i $prob.in
  if ! (time ./sol.exe) ; then
    echo "Fail!"
    exit 1
  fi
  cp $prob.out $i.a
done

rm $prob.{in,out}
