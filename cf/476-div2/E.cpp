#include <bits/stdc++.h>
using namespace std;

const int N = 1e5;
const int ROOT = 0;

int tc = 1;
vector<map<char, int>> to(N);
vector<char> fin(N);
vector<int> sz(N);
vector<long long> dp(N), mxdep(N);

void add(const char* const s)  {
    int node = ROOT;
    for (int i = 0; s[i] != '\0'; ++i) {
        if (to[node].find(s[i]) == to[node].end()) {
            to[node][s[i]] = tc++;
        }
        node = to[node][s[i]];
    }
    fin[node] = true;
}

void go(int v) {
    sz[v] = fin[v];
    mxdep[v] = fin[v];
    for (const auto& [sym, u] : to[v]) {
        go(u);
        sz[v] += sz[u];
        dp[v] += dp[u] + sz[u];
        if (mxdep[v] < mxdep[u] + fin[v]) {
            mxdep[v] = mxdep[u] + fin[v];
            mxu = u;
        }
    }

    if (!fin[v] && mxu != -1) {
        dp[v] -= mxdep[mxu];
    }
}

int main() {
    int n;
    scanf("%d", &n);

    char s[N + 1];
    for (int i = 0; i < n; ++i) {
        scanf(" %s", s);
        add(s);
    }

    long long ans = 0;
    for (const auto& [sym, u] : to[0]) {
        go(u);
        ans += dp[u] + sz[u];
    }

    printf("%lld\n", ans);
}
