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
#include <complex>

#define fi first
#define se second
#define mp make_pair

#define sz(a) (int)a.size()
#define len(s) (int)s.length()

using namespace std;

typedef long long ll;
typedef unsigned long long ull;

const int INF = 1234567890;
const ll INF_LL = LLONG_MAX - INF;
const int MAXN = 1e5;
const int MAXM = 1e4;
const int MOD = 1e9 + 7;
const double eps = 1e-6;

void no() {
 	cout << "No" << endl;
	exit(0);
}

int main() {
    #if __APPLE__
        freopen("input.txt", "r", stdin);
    #else
        freopen("cat.in", "r", stdin);
        freopen("cat.out", "w", stdout);
    #endif

	int a, b;
	cin >> a >> b;

	a *= 60;
	b *= 60;

	int n;
	cin >> n;

	vector<pair<int, int> > t(n);
	for (int i = 0; i < n; i++) {
     	int hh1, mm1, hh2, mm2;
		scanf("%d:%d-%d:%d", &hh1, &mm1, &hh2, &mm2);

		if (hh1 > hh2 || (hh1 == hh2 && mm1 > mm2)) {
			t[i].se += 24 * 60;
		}

		t[i].fi += hh1 * 60 + mm1;
		t[i].se += hh2 * 60 + mm2;
	}

	sort(t.begin(), t.end());
	t.push_back(mp(t[0].fi + 24 * 60, t[0].se + 24 * 60));

	vector<pair<int, int> > sleep;
	for (int i = 0; i < n; i++) {
		if (t[i + 1].fi - t[i].se - 1 >= a) {
		 	sleep.push_back(mp(t[i].se + 1, t[i + 1].fi - 1));
		}
	}
	if (sleep.empty()) {
		if (b == 24) {
         	cout << "Yes" << endl << 0 << endl;
		} else {
         	cout << "No" << endl;
		}
		return 0;
	}

	sleep.push_back(mp(sleep[0].fi + 24 * 60, sleep[0].se + 24 * 60));

	for (int i = 0; i < sz(sleep) - 1; i++) {
		if (sleep[i + 1].fi - sleep[i].se - 1 > b) {
         	no();
		}
	}

	printf("Yes\n%d\n", sz(sleep) - 1);
	for (int i = 0; i < sz(sleep) - 1; i++) {
     	int hh1 = (sleep[i].fi / 60) % 24;
		int mm1 = sleep[i].fi % 60;

		int hh2 = (sleep[i].se / 60) % 24;
		int mm2 = sleep[i].se % 60;

		printf("%02d:%02d-%02d:%02d\n", hh1, mm1, hh2, mm2);
	}
}

