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

    int n;
    scanf("%d", &n);

    vector<int> a(n + n + n);
    for (size_t i = 0; i < a.size(); ++i) {
        scanf("%d", &a[i]);
    }

    multiset<int> q(a.begin(), a.begin() + n), f, p(a.begin() + n, a.end());
    ll sum1 = 0;
    for (int i = 0; i < n; ++i) {
        sum1 += a[i];
    }
    ll sum2 = 0;
    for (int i = 0; i < n; ++i) {
        auto it = p.begin();
        f.insert(*it);
        sum2 += *it;
        p.erase(it);
    }

    ll ans = sum1 - sum2;
    for (int i = n; i < n + n; ++i) {
        auto itf = f.find(a[i]);
        auto itp = p.find(a[i]);
        if (itf != f.end()) {
            sum2 -= a[i];
            f.erase(itf);
            auto it = p.begin();
            f.insert(*it);
            sum2 += *it;
            p.erase(it);
        } else if (itp != p.end()) {
            p.erase(itp);
        }
        sum1 += a[i];
        q.insert(a[i]);
        sum1 -= *q.begin();
        q.erase(q.begin());
        ans = max(ans, sum1 - sum2);
    }

    printf("%lld\n", ans);
}
