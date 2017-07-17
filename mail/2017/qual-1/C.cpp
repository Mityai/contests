#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

using ll = long long;

struct Q {
    ll a, b, x;
};

bool cmp(Q& q1, Q& q2) {
    ll A = (q1.a - q1.b) * q2.x;
    ll B = (q2.a - q2.b) * q1.x;
    if (A < B) {
        return true;
    }
    if (A == B && q1.x == q2.x) {
        return q1.a < q2.a;
    }
    return false;
}

int main() {
#if __APPLE__
    freopen("C.in", "r", stdin);
    freopen("C.out", "w", stdout);
#endif

    int t;
    scanf("%d", &t);

    while (t--) {
        int n;
        scanf("%d", &n);

        vector<Q> g;
        vector<Q> f;
        for (int i = 0; i < n; ++i) {
            Q q;
            scanf("%lld%lld%lld", &q.a, &q.b, &q.x);
            if (q.x == 0) {
                f.push_back(q);
            } else {
                g.push_back(q);
            }
        }

        sort(g.begin(), g.end(), cmp);
        g.insert(g.end(), f.begin(), f.end());
        double sumb = 0;
        for (int i = 0; i < n; ++i) {
            sumb += g[i].b;
        }
        double ans = 0;
        double suma = 0;
        for (int i = 0; i < n; ++i) {
            suma += g[i].a;
            sumb -= g[i].b;
            ans += double(g[i].x) * (suma + sumb);
        }
        printf("%.10lf\n", ans / 1e7);
    }
}
