#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

#if __APPLE__
#define eprintf(...) fprintf(stderr, __VA_ARGS__)
#else
#define eprintf(...)
#endif

const int M = 1e6;

void solve(int n, int A) {
    vector<int> c(n + 1);

    for (int i = 1; i <= n; ++i) {
        scanf("%d", &c[i]);
    }

    vector<int> d(M + 1);
    vector<char> good(M + 1, true);
    good[A] = false;
    set<pair<int, int>> q;
    for (int i = 1; i <= M; ++i) {
        if (good[i]) q.insert({0, i});
    }
    for (int i = 1, cntA = 0; i <= n; ++i) {
        if (c[i] != A) {
            if (good[c[i]]) {
                q.erase({d[c[i]], c[i]});
                ++d[c[i]];
                q.insert({d[c[i]], c[i]});
            }
        } else {
            ++cntA;
            while (!q.empty() && q.begin()->fi < cntA) {
                int v = q.begin()->se;
                q.erase(q.begin());
                good[v] = false;
            }
        }
    }

    if (!q.empty()) {
        printf("%d\n", q.begin()->se);
    } else {
        puts("-1");
    }
}

int main() {
#if __APPLE__
    freopen("D.in", "r", stdin);
    freopen("D.out", "w", stdout);
#endif

    int n, A;
    while (scanf("%d%d", &n, &A) == 2) {
        solve(n, A);
    }
}
