#include <iostream>
#include <algorithm>
using namespace std;


int solve(int* a, int len) {
	if (len == 1) {
		return a[0];
	}

	int l = -solve(a, len / 2);
	int r = -solve(a + len / 2, len / 2);

	return min(l, r);
}

int main() {
	ios_base::sync_with_stdio(false);

	int n;
	cin >> n;

	int* a = new int[n];
	for (int i = 0; i < n; ++i) {
		cin >> a[i];
	}

	cout << solve(a, n) << endl;

	return 0;
}
