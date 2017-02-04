#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

const int INF = 1234567890;
const int MAXN = 100000;

int a[2 * MAXN - 1];

void update(int x, int v, int i, int l, int r) {
 	if (r - l == 1) {
     	a[i] = v;
		return;
	}

	int m = (l + r) / 2;
	if (x < m) {
     	update(x, v, 2 * i + 1, l, m);
	} else {
     	update(x, v, 2 * i + 2, m, r);
	}

	a[i] = min(a[2 * i + 1], a[2 * i + 2]);
}

int getMin(int L, int R, int i, int l, int r) {
 	if (L >= r || l >= R) {
     	return INF;
	}

	if (l <= L && R <= r) {
     	return a[i];
	}
	
	int m = (l + r) / 2;
	return min(getMin(L, R, i * 2 + 1, l, m), getMin(L, R, i * 2 + 2, m, r));
}

int main() {
}
