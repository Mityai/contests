#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

using ll = long long;

const int N = 1e6;

int n;
int fenw[N];

void add(int pos, int val) {
    for (int i = pos; i < n; i = (i | (i + 1))) {
        fenw[i] += val;
    }
}

int sum(int pos) {
    int ret = 0;
    for (int i = pos; i >= 0; i = (i & (i + 1)) - 1) {
        ret += fenw[i];
    }
    return ret;
}

int main() {
#if __APPLE__
    //freopen(".in", "r", stdin);
    //freopen(".out", "w", stdout);
#endif

    int k;
    scanf("%d%d", &n, &k);

    ll ans = 1;
    int x = 0;
    for (int i = 0; i < n; ++i) {
        int cur = sum(x - 1);
        int b = ((x - k) % n + n) % n;
        if (x - k + 1 < 0) {
            cur += sum(n - 1);
        }
        cur -= sum(b);
        add(x, 1);
        x = (x + k) % n;
        printf("%lld ", ans);
    }
    puts("");
}
