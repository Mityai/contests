#include <bits/stdc++.h>
#define sz(X) ((int)(X).size())
using namespace std;

typedef long long ll;

const int MOD = 1e9 + 7;

void add(int &a, int b) {
    a += b;
    if (a >= MOD) a -= MOD;
}

int mult(int a, int b) {
    ll ret = a * 1LL * b;
    if (ret >= MOD) ret %= MOD;
    return (int)ret;
}

vector<vector<int> > mult(vector< vector<int> > &A, vector< vector<int> > &B) {
	vector< vector<int> > C(sz(A), vector<int> (sz(B[0])));
	for (int i = 0; i < sz(C); i++) {
     	for (int j = 0; j < sz(C[i]); j++) {
			for (int k = 0; k < sz(B); k++) {
             	add(C[i][j], mult(A[i][k], B[k][j]));
			}
		}
	}
	return C;
}

vector< vector<int> > E;

vector< vector<int> > bin_pow(vector< vector<int> > &A, int n) {
 	if (n == 0) {
     	return E;
	}

	if (n == 1) {
     	return A;
	}

	vector< vector<int> > B = bin_pow(A, n / 2);
    B = mult(B, B);
	if (n % 2 == 0) {
		return B;
	} else {
		return mult(B, A);
	}
}

int main() {
    vector< vector<int> > A(1, vector<int> (5));
    ll a, b, c, d, e, f;
    scanf("%lld%lld%lld%lld%lld%lld", &a, &b, &c, &d, &e, &f);
    scanf("%d%d%d%d", &A[0][0], &A[0][1], &A[0][2], &A[0][3]);
    A[0][4] = (e * A[0][0] + e * A[0][1] + f * A[0][2] + f * A[0][3]) % MOD;

    vector< vector<int> > P = 
    {{0, 0, 0, (int)d, int((f * d) % MOD)},
     {1, (int)a, 0, 0, int((e * a) % MOD)},
     {0, (int)b, 0, 0, int((e * b) % MOD)},
     {0, 0, 1, (int)c, int((f * c) % MOD)},
     {0, 0, 0, 0, 1}
    };

    E.resize(5, vector<int> (5));
    for (int i = 0; i < 5; i++) E[i][i] = 1;

    int q;
    scanf("%d", &q);

    for (int i = 0; i < q; i++) {
        int n;
        scanf("%d", &n);

        if (n == 0) {
            printf("%lld\n", (e * A[0][0] + f * A[0][2]) % MOD);
            continue;
        }

        auto B = bin_pow(P, n - 1);
        auto R = mult(A, B);
        int ans = R[0][4];
        printf("%d\n", ans);
    }
}
