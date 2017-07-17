#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

int n, k;
double U;

double f(int q, const vector<double>& P) {
    double lb = 0.0, rb = 1.0;
    for (int it = 0; it < 100; ++it) {
        double mb = (lb + rb) / 2;
        double need = 0;
        for (int i = 1; i <= q; ++i) {
            need += max(0.0, mb - P[i]);
        }
        if (need <= U) {
            lb = mb;
        } else {
            rb = mb;
        }
    }
    double minq = (lb + rb) / 2;
    auto pi = P;
    double left = U;
    for (int i = 1; i <= q; ++i) {
        pi[i] = max(P[i], minq);
        left -= pi[i] - P[i];
    }

    for (int i = q + 1; i <= n; ++i) {
        pi[i] = min(1.0, left + P[i]);
        left -= pi[i] - P[i];
    }

    double dp[n + 1][n + 1];
    memset(dp, 0, sizeof dp);
    dp[0][0] = 1.0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= n; ++j) {
            dp[i][j] += dp[i - 1][j] * (1.0 - pi[i]);
            if (j > 0) {
                dp[i][j] += dp[i - 1][j - 1] * pi[i];
            }
        }
    }

    double ans = 0;
    for (int i = k; i <= n; ++i) {
        ans += dp[n][i];
    }
    return ans;
}

int main() {
    freopen("C.in", "r", stdin);
    freopen("C.out", "w", stdout);

    int t;
    scanf("%d", &t);

    for (int test = 1; test <= t; ++test) {
        scanf("%d%d", &n, &k);
        scanf("%lf", &U);

        vector<double> P(n + 1);
        for (int i = 1; i <= n; ++i) {
            scanf("%lf", &P[i]);
        }

        sort(P.rbegin(), P.rend() - 1);

        int lb = 0, rb = n;
        while (lb + 2 < rb) {
            int mb1 = (lb + lb + rb) / 3;
            int mb2 = (lb + rb + rb) / 3;

            if (f(mb1, P) > f(mb2, P)) {
                rb = mb2;
            } else {
                lb = mb1;
            }
        }
        int anst = lb;
        for (int i = lb + 1; i <= rb; ++i) {
            if (f(anst, P) < f(i, P)) {
                anst = i;
            }
        }

        printf("Case #%d: %.10lf\n", test, f(anst, P));
    }
}
