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
  $* > $fn || exit
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

echo "make tests"

echo . > $logfile
makeTest "./gen_rand.exe 239 10 10 1000000000"
makeTest "./gen_rand.exe 239 100 100 1000000000"
makeTest "./gen_rand.exe 239 1000 1000 1000000000"
makeTest "./gen_rand.exe 239 10000 1000 1000000000"
makeTest "./gen_rand.exe 239 100000 1000 1000000000"
makeTest "./gen_rand.exe 239 100000 1000 1"
makeTest "./gen_rand_wide_range.exe 23917 10 10 1000000000"
makeTest "./gen_rand_wide_range.exe 23917 100 100 1000000000"
makeTest "./gen_rand_wide_range.exe 23917 1000 1000 1000000000"
makeTest "./gen_rand_wide_range.exe 23917 10000 1000 1000000000"
makeTest "./gen_rand_wide_range.exe 23917 100000 1000 1000000000"
makeTest "./gen_rand_wide_range.exe 23917 100000 1000 1"


makeTest "./gen_rand_only_find.exe 239 10 10 1000000000"
makeTest "./gen_rand_only_find.exe 239 100 100 1000000000"
makeTest "./gen_rand_only_find.exe 239 1000 1000 1000000000"
makeTest "./gen_rand_only_find.exe 239 10000 10000 1000000000"
makeTest "./gen_rand_only_find.exe 239 100000 100000 1000000000"
makeTest "./gen_rand_only_find.exe 239 100000 100000 1"


makeTest "./gen_rand.exe 2391 10 10 1000000000"
makeTest "./gen_rand.exe 2391 100 100 1000000000"
makeTest "./gen_rand.exe 2391 1000 1000 1000000000"
makeTest "./gen_rand.exe 2391 10000 10000 1000000000"
makeTest "./gen_rand.exe 2391 100000 100000 1000000000"
makeTest "./gen_rand.exe 2391 100000 100000 1"
makeTest "./gen_rand_wide_range.exe 2392 10 10 1000000000"
makeTest "./gen_rand_wide_range.exe 2392 100 100 1000000000"
makeTest "./gen_rand_wide_range.exe 2392 1000 1000 1000000000"
makeTest "./gen_rand_wide_range.exe 2392 10000 10000 1000000000"
makeTest "./gen_rand_wide_range.exe 2392 100000 100000 1000000000"
makeTest "./gen_rand_wide_range.exe 2392 100000 100000 1"

echo "Compiling solution"
g++ -O2 -Wall -I "../graders" -o "sol.exe" "../graders/grader.cpp" "../solutions/kthstat_ra_n_sqrt_nlogn.cpp" || die "Unable to compile"
for f in ?? ; do
  echo "Running on test $f"
  ./sol.exe < $f > $f.a || die "Unable to run"
done

echo "move tests"
testdir="../tests"
rm -f -r $testdir
mkdir $testdir || fail
mv ?? ??.a ../tests/ || exit 1

echo "clean"
rm gen gen.exe

