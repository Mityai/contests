#!/bin/bash

logfile=tests.comments

function die {
  echo "$*"
  exit 1
}

tn=1
function makeTest
{
  fn=`printf "%02d" $tn`
  echo $fn : $* 
  echo $fn : $* >> $logfile
  $* | ./twf.exe > $fn || exit
  let tn=$tn+1
}

function compile
{
  echo compile $1
  g++ -O2 -Wall $1.cpp -o $1.exe || exit
}

compile gen_rand
compile gen_rand_wide_range 
compile gen_rand_only_find
compile gen_rand_add
compile gen_rand_del
compile gen_rand_add
gcc -O2 -Wall -o twf.exe twf.c

echo "make tests"

echo . > $logfile
makeTest "./gen_rand.exe 001 10 10 1000000000"
makeTest "./gen_rand.exe 002 100 100 1000000000"
makeTest "./gen_rand.exe 003 1000 1000 1000000000"
makeTest "./gen_rand.exe 004 100000 1000 1000000000"
makeTest "./gen_rand.exe 005 100000 1000 10"
makeTest "./gen_rand_wide_range.exe 23906 100 100 1000000000"
makeTest "./gen_rand_wide_range.exe 23907 1000 1000 1000000000"
makeTest "./gen_rand_wide_range.exe 23908 10000 1000 1000000000"
makeTest "./gen_rand_wide_range.exe 23909 100000 1000 1000000000"
makeTest "./gen_rand_wide_range.exe 23910 100000 1000 10"


makeTest "./gen_rand_only_find.exe 011 10 10 1000000000"
makeTest "./gen_rand_only_find.exe 012 100 100 1000000000"
makeTest "./gen_rand_only_find.exe 013 1000 1000 1000000000"
makeTest "./gen_rand_only_find.exe 014 10000 10000 1000000000"
makeTest "./gen_rand_only_find.exe 015 100000 100000 10"
makeTest "./gen_rand_only_find.exe 016 100000 100000 100"
makeTest "./gen_rand_only_find.exe 017 100000 100000 5000"
makeTest "./gen_rand_only_find.exe 018 100000 100000 1000000000"


makeTest "./gen_rand.exe 019 100000 100000 1000000000"
makeTest "./gen_rand.exe 020 100000 100000 5000"
makeTest "./gen_rand.exe 021 100000 100000 10"
makeTest "./gen_rand_wide_range.exe 022 100000 100000 1000000000"
makeTest "./gen_rand_wide_range.exe 023 100000 100000 5000"
makeTest "./gen_rand_wide_range.exe 024 100000 100000 10"
makeTest "./gen_rand_add.exe 025 100000 100000 10000"
makeTest "./gen_rand_add.exe 026 100000 100000 1000000000"
makeTest "./gen_rand_del.exe 027 100000 100000 10000"
makeTest "./gen_rand_del.exe 028 100000 100000 1000000000"
makeTest "./gen_rand_only_find.exe 029 100000 100000 10000"
makeTest "./gen_rand_only_find.exe 030 100000 100000 1000000000"



echo "Compiling solution"
g++ -O2 -Wall -I "../graders" -o "sol.exe" "../graders/grader.cpp" "../solutions/kthstat_ra_n_sqrt_nlogn.cpp" || die "Unable to compile"
for f in ?? ; do
  echo "Running on test $f"
  ./sol.exe < $f | ./twf.exe > $f.a || die "Unable to run"
done

echo "move tests"
testdir="../tests"
rm -f -r $testdir
mkdir $testdir || fail
mv ?? ??.a ../tests/ || exit 1
