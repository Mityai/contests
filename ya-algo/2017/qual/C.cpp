#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

const int N = 50;

int a[N];
ll cnt[N], cnt2[N];
vector<int> g[N];

void go(int v) {
    cnt[v] = cnt2[v] = a[v];
    for (int u : g[v]) {
        go(u);
        cnt[v] += cnt[u];
        cnt2[v] += 2 * cnt2[u];
    }
}

int main() {
#if __APPLE__
    //freopen("A.in", "r", stdin);
    //freopen("A.out", "w", stdout);
#endif

    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; ++i) {
        scanf("%d", &a[i]);
    }

    for (int i = 0; i < n; ++i) {
        int k;
        scanf("%d", &k);

        for (int j = 0; j < k; ++j) {
            int x;
            scanf("%d", &x);
            --x;
            g[i].push_back(x);
        }
    }

    go(0);

    printf("%lld %lld\n", cnt[0], cnt2[0]);
}
