#include <bits/stdc++.h>
#define fi first
#define se second

using namespace std;


int const N = 1e5 + 123;
vector<int> g[N];
bool used[N];

bool hasCycle(int v) {
    used[v] = true;
    bool ans = false;
    for (auto u : g[v]) {
        if (used[u])
            return true;
        ans |= hasCycle(u);
    }
    return ans;
}


int main() {
#if __APPLE__
    freopen("B.in", "r", stdin);
    freopen("B.out", "w", stdout);
#else
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    int n, m;
    scanf("%d%d", &n, &m);

    if (n == 1) {
        puts("-1");
        return 0;
    }

    if (m == 0) {
        puts("2");
        return 0;
    }

    set< pair<int, int> > q;
    for (int i = 0; i != m; ++i) {
        int a, b;
        scanf("%d%d", &a, &b);

        q.insert({a, b});
        g[a].push_back(b);
    }
    for (int i = 1; i <= n; ++i) {
        if (!used[i] && hasCycle(i)) {
            cout << 0 << endl;
            return 0;
        }
    }
    for (auto& p : q) {
        if (q.find({p.se, p.fi}) != q.end()) {
            puts("0");
            return 0;
        }
    }

    puts("1");
}
