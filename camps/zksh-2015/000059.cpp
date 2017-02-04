#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, -1, 0, 1};

int n;
ll ans = 0;
bool used[60][60];
int x = 25, y = 25;
int len = 0;

ll val[23];

inline void go() {
	used[x][y] = true;
	val[len]++;
	if (len == n) {
		used[x][y] = false;
		return;
	}

	for (int i = 0; i < 4; i++) {
		x += dx[i];
		y += dy[i];
		if (!used[x][y]) {
			len++;
			go();
			len--;
		}
		x -= dx[i];
		y -= dy[i];
	}
	used[x][y] = false;
}

int main() {
#if __APPLE__
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);	
#else
	freopen("paths.in", "r", stdin);
	freopen("paths.out", "w", stdout);	
#endif

	vector<ll> a;
	a.push_back(1);
	a.push_back(4);
	a.push_back(12);
	a.push_back(36);
	a.push_back(100);
	a.push_back(284);
	a.push_back(780);
	a.push_back(2172);
	a.push_back(5916);
	a.push_back(16268);
	a.push_back(44100);
	a.push_back(120292);
	a.push_back(324932);
	a.push_back(881500);
	a.push_back(2374444);
	a.push_back(6416596);
	a.push_back(17245332);
	a.push_back(46466676);
	a.push_back(124658732);
	a.push_back(335116620);
	a.push_back(897697164);
	a.push_back(2408806028);
	a.push_back(6444560484);

	scanf("%d", &n);
	/*go();
	for (int i = 0; i < 23; i++) {
		cout << val[i] << endl;
	}*/

	cout << a[n] << endl;
}
