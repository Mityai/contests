g++ a.cpp -o a || exit
g++ b.cpp -o b || exit
./a > tmp && ./b < tmp
./a & ./b
./a | ./b
./a || ./b
