#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

int main() {
	int n, m; cin >> n >> m;
	vector<int> a(n - 1), b(n - 1), c(n - 1);
	for (int i = 0; i < n - 1; i++) {
		scanf("%d%d%d", &a[i], &b[i], &c[i]);
	}
	cout << n << " " << m << endl;
	for (int i = 0; i < n - 1; i++) {
		printf("%d %d %d\n", a[i], b[i], c[i]);
	}
	for (int len = n; m > 0 && len >= 1; len--) {
		for (int i = 0; i <= n - len && m > 0; i++) {
			printf("%d %d\n", i + 1, i + len);
			m--;
		}
	}
	return 0;
}