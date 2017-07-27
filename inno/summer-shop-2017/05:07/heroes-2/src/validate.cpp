#include "testlib.h"
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cassert>
#include <ctime>
#include <cstring>
#include <string>
#include <set>
#include <map>
#include <vector>
#include <list>
#include <deque>
#include <queue>
#include <sstream>
#include <iostream>
#include <algorithm>

using namespace std;

#define pb push_back
#define mp make_pair
#define fs first
#define sc second

const double pi = acos(-1.0);

const int minN = 1;
const int maxN = 200 * 1000;
const int minM = 1;
const int maxM = 200 * 1000;
const int minAB = 1;
const int maxAB = 1000 * 1000 * 1000;
const int minCD = 1;
const int maxCD = 200 * 1000;

int main() {
	registerValidation();

	int n = inf.readInt(minN, maxN);
	inf.readSpace();
	int m = inf.readInt(minM, maxM);
	inf.readEoln();

	for (int i = 0; i < n; i++)	{
		inf.readInt(minAB, maxAB);
		inf.readSpace();
		inf.readInt(minAB, maxAB);
		inf.readEoln();
	}
	for (int i = 0; i < m; i++) {
		inf.readInt(minCD, maxCD);
		inf.readSpace();
		inf.readInt(minCD, maxCD);
		inf.readEoln();
	}

	inf.readEof();

    return 0;
}