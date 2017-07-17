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

const int N = 2e5;

vector<int> g[N];
int depth[N];

void go(int v, int d) {
    depth[v] = d;
    for (int u : g[v]) {
        go(u, d + 1);
    }
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);

    vector<int> A(m);
    for (int i = 0; i < m; ++i) {
        scanf("%d", &A[i]);
    }

    for (int i = 0; i < n - 1; ++i) {
        int par;
        scanf("%d", &par);
        g[par - 1].push_back(i + 1);
    }

    go(0, 0);

    sort(depth, depth + n);
    ll ans = 0;
    for (int curd : A) {
        int lb = -1, rb = n;
        while (lb + 1 < rb) {
            int mb = (lb + rb) / 2;
            if (depth[mb] < curd) lb = mb;
            else rb = mb;
        }
        ans += n - rb;
    }
    printf("%lld\n", ans);
}
