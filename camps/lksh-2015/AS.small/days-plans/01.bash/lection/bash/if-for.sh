# (, ((, [, [[, `, ', ", $((
for ((i = 0; i < 100; i++)); do
  echo $i
  a=$i+1
  b=$(($i+1))
  echo $a
  echo $b
  if [ $i == 10 ] || [ $i == 12 ] ; then
    continue
  fi
  sqrt=`echo "from math import *; print(sqrt($i))" | python`
  echo $sqrt
  ./runtime_error.exe || exit
done
