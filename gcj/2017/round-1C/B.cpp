#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

const int T = 24 * 60;
const int INF = 1e9;

void ans(int test, int ch) {
    printf("Case #%d: %d\n", test, ch);
}

int prev(int x) {
    --x;
    if (x < 0) x += T;
    return x;
}

int main() {
    freopen("B.in", "r", stdin);
    freopen("B.out", "w", stdout);

    int t;
    scanf("%d", &t);

    for (int test = 1; test <= t; ++test) {
        int n, m;
        scanf("%d%d", &n, &m);

        vector<int> mark(T, -1);
        for (int i = 0; i < n; ++i) {
            int l, r;
            scanf("%d%d", &l, &r);
            for (int j = l; j < r; ++j) {
                mark[j] = 0;
            }
        }
        for (int i = 0; i < m; ++i) {
            int l, r;
            scanf("%d%d", &l, &r);
            for (int j = l; j < r; ++j) {
                mark[j] = 1;
            }
        }

        int st = -1;
        for (int i = 0; i < T; ++i) {
            if (mark[prev(i)] == 0 && mark[i] != 0) {
                st = i;
            } else if (mark[prev(i)] == 1 && mark[i] != 1) {
                st = i;
            }
        }

        if (st == -1) {
            ans(test, 2);
        } else {
            vector<vector<vector<int>>> dp(T, vector<vector<int>>(T, vector<int>(2, INF)));
            if (mark[prev(st)] == 0) {
                if (mark[st] != 0) {
                    dp[st][1][0] = 1;
                }
                dp[st][0][1] = 0;
            } else {
                dp[st][1][0] = 0;
                if (mark[st] != 1) {
                    dp[st][0][1] = 1;
                }
            }
            for (int i = (st + 1) % T; i != st; i = (i + 1) % T) {
                for (int t = 0; t <= T / 2; ++t) {
                    if (mark[i] == 0) {
                        dp[i][t][1] = min(dp[prev(i)][t][1], dp[prev(i)][t][0] + 1);
                    } else if (mark[i] == 1) {
                        if (t - 1 >= 0) {
                            dp[i][t][0] = min(dp[prev(i)][t - 1][0], dp[prev(i)][t - 1][1] + 1);
                        }
                    } else {
                        dp[i][t][1] = min(dp[prev(i)][t][1], dp[prev(i)][t][0] + 1);
                        if (t - 1 >= 0) {
                            dp[i][t][0] = min(dp[prev(i)][t - 1][0], dp[prev(i)][t - 1][1] + 1);
                        }
                    }
                }
            }
            int ch = min(dp[prev(st)][T / 2][0], dp[prev(st)][T / 2][1]);
            ans(test, ch);
        }
    }
}
