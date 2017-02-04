#!/bin/bash
g++ -std=c++11 testcr.cpp -o testcr
g++ -std=c++11 main.cpp -o main
g++ -std=c++11 slow.cpp -o slow
for (( count = 1; count <= 10; count++ )) do
	echo $count "--------------"
	./testcr
	./main
	./slow
	sleep 0.3
done
exit 0
