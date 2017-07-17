#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

int main() {
#if __APPLE__
    //freopen("A.in", "r", stdin);
    //freopen("A.out", "w", stdout);
#endif

    int n, m;
    scanf("%d%d", &n, &m);

    vector<int> cnt(n);
    for (int i = 0; i < m; ++i) {
        int a, b;
        scanf("%d%d", &a, &b);
        --a, --b;
        ++cnt[a];
        ++cnt[b];
    }

    bool ok = true;
    for (int i = 0; i < n; ++i) {
        ok &= !(cnt[i] & 1);
    }

    if (ok) {
        puts("YES");
    } else {
        puts("NO");
    }
}
