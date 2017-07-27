all: validate.exe check.exe sol.exe

validate.exe: validate.cpp
	g++ -O2 -Wall validate.cpp -o validate.exe

check.exe: ../check.cpp
	g++ -O2 -Wall ../check.cpp -o check.exe

sol.exe: ../solutions/orders_sk_nsqrtn.cpp
	g++ -O2 -Wall ../solutions/orders_sk_nsqrtn.cpp -o sol.exe
