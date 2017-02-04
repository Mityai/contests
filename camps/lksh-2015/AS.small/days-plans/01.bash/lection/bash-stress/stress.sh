function fail {
  echo FAIL
  exit
}

for ((i = 0;; i++)) ; do
  echo $i
  echo $RANDOM $RANDOM > a.in
  ./a.exe < a.in > a.ans || fail
  ./b.exe < a.in > a.out || fail
  diff a.out a.ans || fail
done
