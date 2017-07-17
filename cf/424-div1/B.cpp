#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

const int N = 1e5;

int n;
int fenw[N];

void add(int pos, int val) {
    for (int i = pos; i < n; i = (i | (i + 1))) {
        fenw[i] = max(fenw[i], val);
    }
}

int getmax(int pos) {
    int ret = 0;
    for (int i = pos; i >= 0; i = (i & (i + 1)) - 1) {
        ret = max(ret, fenw[i]);
    }
    return ret;
}

int main() {
#if __APPLE__
    freopen("B.in", "r", stdin);
    freopen("B.out", "w", stdout);
#endif

    scanf("%d", &n);

    map<int, vector<int>> pos;
    for (int i = 0; i < n; ++i) {
        int x;
        scanf("%d", &x);
        pos[x].push_back(i);
    }

    ll ans = 0;
    int mx = 0;
    for (auto& v : pos) {
        int cur_mx = 0;
        for (int p : v.se) {
            int cur = max(mx, getmax(n - p - 1) + 1);
            ans += cur;
            add(n - p - 1, cur);
            cur_mx = max(cur_mx, cur);
        }
        mx = max(mx, cur_mx);
    }

    printf("%lld\n", ans);
}
