#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <string>
#include <cstring>
#include <cmath>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <iomanip>
#include <sstream>
#include <climits>
#include <bitset>

#define frs first
#define scn second
#define mp make_pair

#define sz(a) a.size()
#define len(s) s.length()

using namespace std;

typedef long long ll;
typedef unsigned long long ull;

const int INF = 1234567890;
const ll INF_LL = LLONG_MAX - INF;
const int MAXN = 1e5;
const int MAXM = 1e4;
const int MOD = 1e9 + 7;
const double eps = 1e-6;

void prm(int n, map<int, int> &a) {
 	int p = 2;
	int m = n;
	while (p * p <= m && n > 1) {
		int cnt = 0;
     	while (n % p == 0) {
         	n /= p;
			++cnt;
		}

		if (cnt > 0) {
         	a[p] = cnt;
		}

		++p;
	}

	if (n != 1) {
     	a[n] = 1;
	}
}

int main() {
    #if __APPLE__
        freopen("input.txt", "r", stdin);
    #else
        freopen("bacteria.in", "r", stdin);
        freopen("bacteria.out", "w", stdout);
    #endif

	int n, m;
	cin >> n >> m;

	map<int, int> a, b;
	prm(n, a);
	prm(m, b);

	vector<int> del;
	for (map<int, int>::iterator it = b.begin(); it != b.end(); it++) {
     	if (a.find(it->first) == a.end()) {
        	cout << "Impossible" << endl;
			return 0;
		}
		del.push_back(it->first);
	}

	for (map<int, int>::iterator it = a.begin(); it != a.end(); it++) {
     	if (b.find(it->first) == b.end()) {
         	int cnt = it->second;
			for (int i = 0; i < cnt; i++) {
             	cout << it->first << ' ';
			}
		}
	}

	vector<int> ans;
	while (true) {
		bool ok = true;
		for (map<int, int>::iterator it = b.begin(); it != b.end(); it++) {
			if (it->second > a[it->first]) {
				ok = false;
			}
		}
		if (ok) {
         	break;
		}

		for (map<int, int>::iterator it = b.begin(); it != b.end(); it++) {
			if (it->second % 2 == 1) {
				it->second++;
				ans.push_back(it->first);
			}
			
			it->second /= 2;
		}
		ans.push_back(0);
	}

	for (map<int, int>::iterator it = b.begin(); it != b.end(); it++) {
     	for (int i = 0; i < a[it->first] - it->second; i++) {
         	ans.push_back(it->first);
		}
	}

	for (int i = sz(ans) - 1; i >= 0; i--) {
     	cout << ans[i] << ' ';
	}
}
