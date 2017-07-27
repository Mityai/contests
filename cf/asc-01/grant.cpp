#include <bits/stdc++.h>
using namespace std;

const int N = 5e5;

vector<int> g[N];
int dp[N][2], to[N];

void go(int v) {
    int sum0 = 0;
    for (int u : g[v]) {
        go(u);
        sum0 += dp[u][0];
    }
    dp[v][1] = sum0 + 1;
    int mx = sum0;
    to[v] = -1;
    for (int u : g[v]) {
        if (mx < sum0 - dp[u][0] + dp[u][1]) {
            mx = sum0 - dp[u][0] + dp[u][1];
            to[v] = u;
        }
    }
    dp[v][0] = mx;
}

vector<int> ans;

void rev(int v, int t) {
    if (t == 1) {
        ans.push_back(v + 1);
        for (int u : g[v]) {
            rev(u, 0);
        }
    } else {
        for (int u : g[v]) {
            if (to[v] == u) {
                rev(u, 1);
            } else {
                rev(u, 0);
            }
        }
    }
}

int main() {
    freopen("grant.in", "r", stdin);
    freopen("grant.out", "w", stdout);

    int n;
    scanf("%d", &n);

    for (int i = 1; i < n; ++i) {
        int p;
        scanf("%d", &p);
        g[p - 1].push_back(i);
    }

    go(0);
    printf("%d\n", dp[0][0] * 1000);
    rev(0, 0);
    sort(ans.begin(), ans.end());
    for (int x : ans) {
        printf("%d ", x);
    }
    puts("");
}
