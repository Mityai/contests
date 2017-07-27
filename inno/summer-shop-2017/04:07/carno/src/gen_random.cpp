#include "testlib.h"
#include <iostream>
#include <set>

using namespace std;

const int N = 200100;

int countVertex = 0;
bool exists[N];

void createVertex()
{
	int currentVertex = countVertex++;
	exists[currentVertex] = true;
}

void deleteVertex(int currentVertex)
{
	ensure(exists[currentVertex]);
	exists[currentVertex] = false;
}

int genExistingVertex(const bool notRoot, const bool notNull)
{
	for (int iter = 0; notNull || iter < 100; ++iter)
	{
		int v = rnd.next(0, countVertex - 1);
		if (!exists[v])
			continue;
		if (notRoot && v == 0)
			continue;
		return v;
	}
	return -1;
}

int main(int argc, char** argv) {
    registerGen(argc, argv);

    int n = atoi(argv[1]);
    int m = atoi(argv[2]);

    printf("%d\n", n);
    createVertex();
    for (int i = 0; i < n; ) {
        int type = rnd.next(0, 2);
        if (type == 0)
        {
        	int v = genExistingVertex(false, true);
        	createVertex();
        	printf("+ %d\n", v + 1);
        } else if (type == 1) {
        	int v = genExistingVertex(true, false);
        	if (v == -1)
        		continue;
        	deleteVertex(v);
        	printf("- %d\n", v + 1);
        } else if (type == 2) {
        	int v = genExistingVertex(false, true);
        	int u = genExistingVertex(false, true);
        	printf("? %d %d\n", u + 1, v + 1);
        } else
        	ensure(false);

        ++i;
    }
    return 0;
}
