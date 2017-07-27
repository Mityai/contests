#!/bin/bash

function fail
{
  echo "Fail!"
  exit 1
}

function make
{
  echo "Compile $1"
  if ! (g++ -O2 -Wall $1.$2 -o $1.exe) ; then
    fail
  fi
}

logfile=tests.comments
rm $logfile
function nextTest
{
  ti=`printf "%02d" "$nt"`
  echo "$1 > $ti" >> $logfile
  echo "$1 > $ti"
  $1 | ./twf.exe > ../tests/$ti || fail
  let nt=$nt+1
  let base=$base+1
}

testdir="../tests"
programs="split gen_rand gen_rand2 gen_all gen3_max gen4_max gen5_max gen6_max gen7_max gen8_max gen9_max genA_max"
nt=1
base=23917

echo "Clear enviroment"
rm -f -r $testdir
mkdir $testdir || fail

echo "Compiling programs"
for prog in $programs ; do
  make $prog cpp
done
make twf c

echo "Generate tests"

echo "Copy manual tests"
for i in `ls *.manual` ; do
  nextTest "cat $i"
done

echo "Split small tests"
rm *.tmp
cat tests.!!! | ./twf.exe | ./split.exe || fail
for i in `ls *.tmp` ; do
  nextTest "cat $i"
done
rm *.tmp

echo "Random tests"

# tn n k [C]
nextTest "./gen_rand.exe $base 15000 6 4 20" # a lot of small tests
nextTest "./gen_rand2.exe $base 15000 6 3" # a lot of small tests
nextTest "./gen_rand2.exe $base 5000 20 10" # a lot of small tests
nextTest "./gen_rand2.exe $base 50000 2 1" # a lot of small tests

# tn n k C
nextTest "./gen_rand.exe $base 10 3 10 100"
nextTest "./gen_rand.exe $base 10 3 100 1000"
nextTest "./gen_rand.exe $base 10 10 100 1000"
nextTest "./gen_rand.exe $base 10 100 100 1000"
nextTest "./gen_rand.exe $base 1 100000 1000 1000000000"

# tn n k 
nextTest "./gen_rand2.exe $base 1 100000 5"
nextTest "./gen_rand2.exe $base 1 100000 50"
nextTest "./gen_rand2.exe $base 1 100000 500"
nextTest "./gen_rand2.exe $base 1 100000 5000"
nextTest "./gen_rand2.exe $base 1 100000 50000"

# tn n k C
nextTest "./gen_all.exe $base 10 10 10 1000000000"
nextTest "./gen_all.exe $base 10 10 9000 1000000000"
nextTest "./gen_all.exe $base 1 42 99000 1000000000"

echo "Max tests"

# tn n k C [len]
nextTest "./gen3_max.exe $base 1 100000 50000 1000000000"
nextTest "./gen4_max.exe $base 1 100000 50000 1000000000 15"
nextTest "./gen5_max.exe $base 1 100000 50000 1000000000 15"

# tn n k [len]
nextTest "./gen6_max.exe $base 1 100000 100000 20"
nextTest "./gen7_max.exe $base 1 100000 100000 20"
nextTest "./gen8_max.exe $base 1 100000 50000"

# tn
nextTest "./gen9_max.exe $base 100000" # a lot of small tests
nextTest "./genA_max.exe $base 100000" # max input

echo "Good tests"

echo "Cleaning up"
for prog in $programs ; do
	rm $prog $prog.exe 2>/dev/null
done

bash validate.sh
bash genans.sh
