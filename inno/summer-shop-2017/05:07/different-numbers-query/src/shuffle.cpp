#include "testlib.h"
#include <vector>
#include <iostream>

#define all(x) (x).begin(), (x).end()
#define mp make_pair
#define fs first
#define sc second
#define pb push_back
#define len(a) ((int) (a).size())

using namespace std;

const int C = 1e9;

int main(int argc, char **argv) {
	registerGen(argc, argv, 1);
	int n, m; cin >> n >> m;
	vector<pair<pair<int, int>, int>> e;
	for (int i = 1; i < n; i++) {
		int u, v, c; scanf("%d%d%d", &u, &v, &c), u--, v--;
		e.pb(mp(mp(u, v), c));
	}
	vector<int> s(n);
	for (int i = 0; i < n; i++) {
		s[i] = i;
	}
	shuffle(all(s));
	for (int i = 0; i < len(e); i++) {
		e[i].fs.fs = s[e[i].fs.fs];
		e[i].fs.sc = s[e[i].fs.sc];
		if (rnd.next(0, 1)) {
			swap(e[i].fs.fs, e[i].fs.sc);
		}
	}
	shuffle(all(e));
	cout << n << " " << m << endl;
	for (int i = 0; i < len(e); i++) {
		printf("%d %d %d\n", e[i].fs.fs + 1, e[i].fs.sc + 1, e[i].sc);
	}
	vector<pair<int, int>> req;
	for (int i = 0; i < m; i++) {
		int u, v; scanf("%d%d", &u, &v), u--, v--;
		req.pb(mp(s[u] + 1, s[v] + 1));
	}
	shuffle(all(req));
	for (int i = 0; i < m; i++) {
		printf("%d %d\n", req[i].fs, req[i].sc);
	}
	return 0;
}