#include <iostream>
#include <cassert>

using namespace std;

#include "testlib.h"

int main () {
	registerValidation ();

	int n = inf.readInt (0, 100000);
	inf.readEoln();
	for (int i = 0; i < n; i ++) {
		inf.readInt (-1000000000, 1000000000);
		if (i + 1 < n)
			inf.readSpace();
		else
			inf.readEoln();
	}
	int k = 0;
	bool add_del = 0;
	while (!inf.seekEof()) {
		char c;
		k ++;
		c = inf.readChar ();
		inf.readSpace ();
		if (c == '-') {
			inf.readInt (0, n-1);
			add_del = 1;
			n --;
		} else
		if (c == '+') {
			add_del = 1;
			inf.readInt (0, n);
			n ++;
			inf.readSpace ();
			inf.readInt (-1000000000, 1000000000);
		} else 
		if (c == '?') {
			int l =	inf.readInt (0, n-1);
			inf.readSpace ();
			inf.readInt (l, n-1);
			inf.readSpace ();
			inf.readInt (-1000000000, 1000000000);
		} else
			ensure (false);
		inf.readEoln();
	}
	inf.readEof();
	ensure (k <= 100000);
	if (k <= 1000)
		fprintf(stderr, "Group 1: k<=1000\n");
	else
	if (add_del == 0)
		fprintf(stderr, "Group 2: only gets\n");
	else
		fprintf(stderr, "Group 3: k<=100000\n");
	return 0;
}
