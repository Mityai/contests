#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

bool cmp(pair<int, int>& a, pair<int, int>& b) {
    return a.fi < b.fi || (a.fi == b.fi && a.se > b.se);
}

int main() {
#if __APPLE__
    freopen("C.in", "r", stdin);
    freopen("C.out", "w", stdout);
#endif

    ll n, c, d;
    scanf("%lld%lld%lld", &n, &c, &d);

    vector<pair<int, int>> a, b;
    for (int i = 0; i < n; ++i) {
        int x, p;
        char c;
        scanf("%d%d %c", &x, &p, &c);

        if (c == 'C') {
            a.push_back({p, x});
        } else {
            b.push_back({p, x});
        }
    }

    sort(a.begin(), a.end(), cmp);
    sort(b.begin(), b.end(), cmp);

    vector<int> pa(a.size());
    for (int i = 0; i < a.size(); ++i) {
        pa[i] = a[i].se;
        if (i > 0) {
            a[i].se = max(a[i].se, a[i - 1].se);
        }
    }
    vector<int> pb(b.size());
    for (int i = 0; i < b.size(); ++i) {
        pb[i] = b[i].se;
        if (i > 0) {
            b[i].se = max(b[i].se, b[i - 1].se);
        }
    }

    int ans_max_a = -1;
    for (int i = 0; i < a.size(); ++i) {
        if (a[i].fi <= c) {
            ans_max_a = a[i].se;
        }
    }
    int ans_max_b = -1;
    for (int i = 0; i < b.size(); ++i) {
        if (b[i].fi <= d) {
            ans_max_b = b[i].se;
        }
    }

    int ans_both;
    if (ans_max_a == -1 || ans_max_b == -1) {
        ans_both = 0;
    } else {
        ans_both = ans_max_a + ans_max_b;
    }

    int ans1 = 0;
    for (int i = 0; i < a.size(); ++i) {
        int lb = -1, rb = i;
        while (lb + 1 < rb) {
            int mb = (lb + rb) / 2;
            if (a[mb].fi + a[i].fi <= c) {
                lb = mb;
            } else {
                rb = mb;
            }
        }
        if (lb != -1) {
            ans1 = max(ans1, a[lb].se + pa[i]);
        }
    }

    int ans2 = 0;
    for (int i = 0; i < b.size(); ++i) {
        int lb = -1, rb = i;
        while (lb + 1 < rb) {
            int mb = (lb + rb) / 2;
            if (b[mb].fi + b[i].fi <= d) {
                lb = mb;
            } else {
                rb = mb;
            }
        }
        if (lb != -1) {
            ans2 = max(ans2, b[lb].se + pb[i]);
        }
    }

    int ans = max({ans_both, ans1, ans2});
    printf("%d\n", ans);
}
