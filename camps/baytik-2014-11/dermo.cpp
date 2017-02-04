#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <iomanip>
#include <sstream>
#include <climits>
   
#define fi first
#define se second
#define mp make_pair
   
#define sz(a) a.size()
#define len(s) s.length()
   
using namespace std;
   
typedef long long ll;
   
const int INF = 1234567890;
const int MAXN = 1e5;
const int MOD = 1e9 + 7;
const double eps = 1e-6;

bool cmp(pair<int, int> p1, pair<int, int> p2) {
	return p1.fi < p2.fi || (p1.fi == p2.fi && p1.se > p2.se);
}

int main() {
    #if __APPLE__
        freopen("input.txt", "r", stdin);
    #else
        freopen("toy.in", "r", stdin);
        freopen("toy.out", "w", stdout);
    #endif

	int n;
	cin >> n;

	vector<int> a(n + 1);
	for (int i = 1; i <= n; i++) {
     	cin >> a[i];
	}

	int m;
	cin >> m;

	vector<int> plus(n + 2);
	vector<pair<int, int> > seg;
	for (int i = 0; i < m; i++) {
     	int l, r;
		cin >> l >> r;

		++r;

		seg.push_back(mp(l, r));
		
		++plus[l];
		--plus[r];
	}

	int cur = 0;
	vector<int> b(n + 1), sum(n + 1);
	set<int> pt;
	for (int i = 1; i <= n; i++) {
		cur += plus[i];
		b[i] = max(0, cur - a[i]);

		if (b[i] > 0) {
			pt.insert(i);
		}
	}

	sort(seg.begin(), seg.end());
	int ans = 0;

	multiset<int> en;
	vector<int> t(n + 2);
	int v = 0;
	for (int i = 1, j = 0; i <= n; i++) {
		v += t[i];
		if (pt.find(i) != pt.end()) {
			int u = i;
			for (; j < seg.size() && seg[j].fi <= i; j++) {
				if (i < seg[j].se) {
					en.insert(seg[j].se);
				}
			}

			int cur = b[i] - v;
			if (cur > 0) {
				ans += cur;
				int co = cur;
				for (int k = 0; k < co; k++) {
					set<int>::reverse_iterator it = en.rbegin();
					++v;
					t[*it] += -1;
					en.erase(--en.end());
				}
			}
		}
	}
	
	cout << ans << endl;
}
