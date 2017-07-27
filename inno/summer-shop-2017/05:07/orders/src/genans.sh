#!/bin/bash

make sol.exe

prob=orders

for i in `ls ../tests/??` ; do
  echo "Test $i"
  cp $i $prob.in
  if ! (time ./sol.exe) ; then
    echo "Fail!"
    exit 1
  fi
  cp $prob.out $i.a
done

rm $prob.{in,out}
