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

ll p = ll(1e9) + 7;

vector<vector<ll> > mult(vector<vector<ll> > A, vector<vector<ll> > B) {
	vector<vector<ll> > C(sz(A), vector<ll> (sz(B[0])));
	for (int i = 0; i < sz(C); i++) {
     	for (int j = 0; j < sz(C[i]); j++) {
			for (int k = 0; k < sz(B); k++) {
             	C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % p;
			}
		}
	}
	return C;
}

vector<vector<ll> > E;

vector<vector<ll> > bin_pow(vector<vector<ll> > A, ll n) {
 	if (n == 0) {
     	return E;
	}

	if (n == 1) {
     	return A;
	}

	vector<vector<ll> > B = bin_pow(A, n / 2);
	if (n % 2 == 0) {
		return mult(B, B);
	} else {
		return mult(mult(B, B), A);
	}
}

int main() {
    #if __APPLE__
        freopen("input.txt", "r", stdin);
    #else
        freopen("fibonacci.in", "r", stdin);
        freopen("fibonacci.out", "w", stdout);
    #endif
	
	ll k, n;
	cin >> k >> n;

	vector<vector<ll> > F(1, vector<ll> (k + 1));
	for (int i = 0; i < k; i++) {
     	cin >> F[0][i];
	}
	F[0][k] = F[0][0];

	vector<vector<ll> > P(k + 1, vector<ll> (k + 1));
	for (int i = 0; i < k; i++) {
     	cin >> P[k - i - 1][k - 1];
	}

	for (int i = 0; i < k - 1; i++) {
     	P[i + 1][i] = 1;
	}

	E.resize(k + 1, vector<ll> (k + 1));
	for (int i = 0; i < k + 1; i++) {
     	E[i][i] = 1;
	}

	P[1][k] = 1;
	P[k][k] = 1;

	P = bin_pow(P, n);
	F = mult(F, P);

	cout << F[0][0] << ' ' << F[0][k] << endl;
}

