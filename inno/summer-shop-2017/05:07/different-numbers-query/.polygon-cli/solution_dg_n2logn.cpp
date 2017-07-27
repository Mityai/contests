#include <iostream>
#include <fstream>
#include <sstream>

#include <vector>
#include <set>
#include <bitset>
#include <map>
#include <deque>
#include <string>

#include <algorithm>
#include <numeric>

#include <cstdio>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cmath>

#define pb push_back
#define pbk pop_back
#define mp make_pair
#define fs first
#define sc second
#define all(x) (x).begin(), (x).end()
#define foreach(i, a) for (__typeof((a).begin()) i = (a).begin(); i != (a).end(); ++i)
#define len(a) ((int) (a).size())

#ifdef CUTEBMAING
#define eprintf(...) fprintf(stderr, __VA_ARGS__)
#else
#define eprintf(...) 42
#endif

using namespace std;

typedef long long int64;
typedef long double ld;
typedef unsigned long long lint;

const int inf = (1 << 30) - 1;
const int64 linf = (1ll << 62) - 1;
const int N = 1e6 + 100;
const int K = 20;
const int C = 500;

int n, q;
vector<pair<int, int>> g[N];

vector<int> st;

bool path(int u, int v, int p = -1) {
	if (u == v) {
		return true;
	}
	for (auto to : g[u]) {
		if (to.fs != p) {
			st.pb(to.sc);
			if (path(to.fs, v, u)) {
				return true;
			}
			st.pbk();
		}
	}
	return false;
}

inline int mex(const vector<int> &st) {
    set<int> s(all(st));
    for (int i = 0;; i++) {
        if (s.count(i) == 0) {
            return i;
        }
    }
    assert(false);
}

int main() {
	cin >> n >> q;
	for (int i = 0; i < n - 1; i++) {
		int a, b, c; cin >> a >> b >> c;
		a--, b--;
		g[a].pb(mp(b, c));
		g[b].pb(mp(a, c));
	}
	for (int i = 0; i < q; i++) {
		st.clear();
		int a, b; cin >> a >> b;
		a--, b--;
		assert(path(a, b));
		cout << mex(st) << endl;
	}
    return 0;
}
