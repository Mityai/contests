#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct A {
    int a, b, c;
};

bool cmp(const A& f, const A& g) {
    return f.a - f.b > g.a - g.b;
}

int main() {
    int x, y, z;
    scanf("%d%d%d", &x, &y, &z);

    int n = x + y + z;
    vector<A> a(n);
    ll sum_c = 0;
    for (int i = 0; i < n; ++i) {
        scanf("%d%d%d", &a[i].a, &a[i].b, &a[i].c);
        sum_c += a[i].c;
    }

    sort(a.begin(), a.end(), cmp);
    multiset<int, greater<int>> fi, se, not_in_se;
    ll sum_x = 0, sum_y = 0;
    for (int i = 0; i < n; ++i) {
        sum_y += a[i].b - a[i].c;
        se.insert(a[i].b - a[i].c);
        if (se.size() > y) {
            sum_y -= *se.rbegin();
            not_in_se.insert(*se.rbegin());
            se.erase(--se.end());
        }
    }

    ll ans = 0;
    for (int i = 0; i + y < n; ++i) {
        auto it_del = se.find(a[i].b - a[i].c);
        if (it_del != se.end()) {
            sum_y -= *it_del;
            se.erase(it_del);
        } else {
            it_del = not_in_se.find(a[i].b - a[i].c);
            if (it_del != not_in_se.end()) {
                not_in_se.erase(it_del);
            }
        }
        if (se.size() < y) {
            sum_y += *not_in_se.begin();
            se.insert(*not_in_se.begin());
            not_in_se.erase(not_in_se.begin());
        }
        sum_x += a[i].a - a[i].c;
        fi.insert(a[i].a - a[i].c);
        if (fi.size() > x) {
            sum_x -= *fi.rbegin();
            fi.erase(--fi.end());
        }
        if (fi.size() == x && se.size() == y) {
            ans = max(ans, sum_x + sum_y + sum_c);
        }
    }

    printf("%lld\n", ans);
}
