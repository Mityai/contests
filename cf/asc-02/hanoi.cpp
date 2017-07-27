#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ll;

const ll INF = ULLONG_MAX;

struct Solve {
    int n, m;
    vector<vector<ll>> dp;
    vector<vector<int>> pg;

    Solve(int n, int m) : n(n), m(m) {
        dp.resize(n + 1, vector<ll>(m + 1, INF));
        for (int i = 1; i <= n; ++i) {
            dp[i][1] = 0;
        }
        for (int i = 2; i <= m; ++i) dp[1][i] = 1;
        for (int i = 1; i <= n; ++i) {
            for (int j = 3; j <= m; ++j) {
                for (int k = 1; k < i; ++k) {
                    if (dp[k][j] != INF && dp[i - k][j - 1] != INF) {
                        dp[i][j] = min(dp[i][j], 2 * dp[k][j] + dp[i - k][j - 1]);
                    }
                }
            }
        }

        printf("%lld\n", dp[n][m]);
        pg.resize(m);
        for (int i = n - 1; i >= 0; --i) pg[0].push_back(i);
        go(n, m, 0, m - 1);
    }

    void move(int from, int to) {

        printf("move %d from %d to %d", pg[from].back() + 1, from + 1, to + 1);
        if (!pg[to].empty()) {
            assert(pg[from].back() < pg[to].back());
            printf(" atop %d", pg[to].back() + 1);
        }
        puts("");
        pg[to].push_back(pg[from].back());
        pg[from].pop_back();
    }

    void go(int disks, int pegs, int from, int to) {
        if (pegs == 1) {
            return;
        }
        if (disks == 1) {
            move(from, to);
            return;
        }
        int k;
        for (k = 1; k < disks; ++k) {
            if (dp[k][pegs] != INF && dp[disks - k][pegs - 1] != INF) {
                if (dp[disks][pegs] == 2 * dp[k][pegs] + dp[disks - k][pegs - 1]) {
                    break;
                }
            }
        }
        int unused = -1;
        for (int j = 0; j < m; ++j) {
            if ((pg[j].empty() || pg[from].back() < pg[j].back()) && j != from && j != to) {
                unused = j;
                break;
            }
        }
        assert(unused != -1);
        go(k, pegs, from, unused);
        go(disks - k, pegs - 1, from, to);
        go(k, pegs, unused, to);
    }
};

int main() {
    freopen("hanoi.in", "r", stdin);
    freopen("hanoi.out", "w", stdout);

    int n, m;
    scanf("%d%d", &n, &m);
    Solve solver(n, m);
}
