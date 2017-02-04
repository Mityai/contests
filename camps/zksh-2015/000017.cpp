#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
#if __APPLE__
	freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);	
#endif

	int a[4];
	for (int i = 0; i < 4; i++) {
		cin >> a[i];
	}

	sort(a, a + 4);

	cout << a[0] * a[2] << endl;
}
