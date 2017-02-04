#include <bits/stdc++.h>
#define mp make_pair
#define fi first
#define se second
using namespace std;

typedef long long ll;

const int INF = 1234567890;

const int MAXN = 1111;
const int MAXB = 5111;

int main() {
#if __APPLE__
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);	
#else
	//freopen("paths.in", "r", stdin);
	//freopen("paths.out", "w", stdout);
#endif

	string s;
	cin >> s;

	vector<int> A(1, 0);
	int B = 0;
	{
		int i;
		for (i = 0; s[i] != '='; i++) {
			A.push_back(s[i] - '0');
		}
		A.push_back(1);
		for (i++; i < (int)s.length(); i++) {
			B = B * 10 + (s[i] - '0');
		}
	}

	int n = (int)A.size() - 2;
	vector<int> next(n + 1);
	for (int i = n, nonzero = n + 1; i >= 0; i--) {
		next[i] = nonzero;
		if (A[i] != 0) {
			nonzero = i;
		}
	}

	vector<vector<int> > dp(MAXN + 1, vector<int> (MAXB + 1, -1));
	vector<vector<pair<int, int> > > p(MAXN + 1, vector<pair<int, int> > (MAXB + 1, mp(-1, -1)));

	dp[0][0] = 0;

	int lastwithans = 0;
	for (int i = 0; i < n; i++) {
		for (int j = next[i] + 1, cur = A[next[i]]; j <= n + 1 && j < next[i] + 5; cur = cur * 10 + A[j], j++) {
			//cout << i << ' ' << j - 1 << ' ' << cur << endl;
			for (int k = 0; k <= B - cur; k++) {
				if (dp[i][k] != -1 && (dp[j - 1][k + cur] == -1 || dp[j - 1][k + cur] > dp[i][k] + 1)) {
					dp[j - 1][k + cur] = dp[i][k] + 1;
					p[j - 1][k + cur] = {i, k};
				}
			}
		}
	}

	int mn = INF;
	for (int i = n; i >= 0; i--) {
		if (dp[i][B] != -1 && dp[i][B] < mn) {
			mn = dp[i][B];
			lastwithans = i;
		}
		if (A[i] != 0) {
			break;
		}
	}
	/*for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= B; j++) {
			cout << dp[i][j] << ' ';
		}
		cout << endl;
	}*/
	//cout << dp[lastwithans][B] - (lastwithans == n) << endl;

	assert(dp[lastwithans][B] >= 0);

	vector<int> ps;
	for (int i = lastwithans, j = B; i != 0;) {
		if (i != n) {
			ps.push_back(i);
		}
		int ri = p[i][j].fi, rj = p[i][j].se;
		i = ri;
		j = rj;
	}

	reverse(ps.begin(), ps.end());
	int j = 0;
	for (int i = 1; i <= n; i++) {
		printf("%d", A[i]);
		while (j < (int)ps.size() && ps[j] < i) j++;
		if (j < (int)ps.size() && ps[j] == i) {
			printf("+");
		}
	}
	printf("=%d\n", B);
}
