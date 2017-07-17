#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

const int N = 1e6;

int n;
bool x[N + 1];
int dp[N + 1][2][2];

inline int f(bool a, bool b) {
    return (a << 1) + b;
}

int get(int k) {
    memset(dp, 127, sizeof dp);
    const int INF = dp[0][0][0];
    dp[1][x[1]][0] = 0;
    dp[1][x[1] ^ 1][1] = 1;
    for (int i = 2; i <= n; ++i) {
        dp[i][x[i]][0] = dp[i - 1][k][0];
        dp[i][x[i] ^ 1][0] = dp[i - 1][k][1];
        dp[i][x[i] ^ 1][1] = dp[i - 1][k ^ 1][0] + 1;
        dp[i][x[i]][1] = dp[i - 1][k ^ 1][1] + 1;
    }

    int ret = min(dp[n][k][0], dp[n][k][1]);
    if (ret == INF) ret = -1;
    return ret;
}

int nextInt() {
    char c = getchar();
    while (c <= 32) c = getchar();
    int ret = 0;
    while ('0' <= c && c <= '9') {
        ret = ret * 10 + c - '0';
        c = getchar();
    }
    return ret;
}

bool nextB() {
    char c = getchar();
    while (c <= 32) c = getchar();
    char last;
    while ('0' <= c && c <= '9') {
        last = c;
        c = getchar();
    }
    return last & 1;
}

int main() {
#if __APPLE__
    freopen("D.in", "r", stdin);
    freopen("D.out", "w", stdout);
#endif

    n = nextInt();

    for (int i = 1; i <= n; ++i) {
        x[i] = nextB();
    }

    int ans1 = get(1);
    int ans2 = get(0);

    printf("%d\n%d\n", ans1, ans2);
}
