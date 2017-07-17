#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

#if __APPLE__
#define eprintf(...) fprintf(stderr, __VA_ARGS__)
#else
#define eprintf(...)
#endif

const int MOD = 1e9 + 7;

void add(int& x, int y) {
    x += y;
    if (x >= MOD) x -= MOD;
}

void sub(int& x, int y) {
    x = (x - y) % MOD;
    if (x < 0) x += MOD;
}

int main() {
#if __APPLE__
    //freopen("A.in", "r", stdin);
    //freopen("A.out", "w", stdout);
#endif

    int n;
    scanf("%d", &n);

    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &a[i]);
    }

    sort(a.begin(), a.end());

    vector<int> pw(n + 1);
    pw[0] = 1;
    for (int i = 1; i <= n; ++i) {
        pw[i] = (pw[i - 1] * 2ll) % MOD;
    }

    int ans = 0;
    int sum = 0;
    for (int i = 0; i < n; ++i) {
        int cur = (pw[i] * 1ll * a[i]) % MOD;
        add(ans, cur);
        cur = (pw[n - i - 1] * 1ll * a[i]) % MOD;
        sub(ans, cur);
    }

    printf("%d\n", ans);
}
