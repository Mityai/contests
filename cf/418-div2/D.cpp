#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

const double pi = acos(-1);

struct C {
    ll x, y, r;
};

bool cmpr(const C& a, const C& b) {
    return a.r > b.r;
}

double sqr(double x) {
    return x * x;
}

int main() {
#if __APPLE__
    //freopen("A.in", "r", stdin);
    //freopen("A.out", "w", stdout);
#endif

    int n;
    scanf("%d", &n);

    vector<C> a(n);
    for (int i = 0; i < n; ++i) {
        scanf("%lld%lld%lld", &a[i].x, &a[i].y, &a[i].r);
    }

    sort(a.begin(), a.end(), cmpr);

    vector<int> lvl(n);
    double ans = 0;
    for (int i = 0; i < n; ++i) {
        bool found = false;
        for (int j = i - 1; j >= 0; --j) {
            if (sqr(a[j].x - a[i].x) + sqr(a[j].y - a[i].y) <= sqr(a[j].r)) {
                lvl[i] = lvl[j] + 1;
                found = true;
                break;
            }
        }
        if (lvl[i] == 0 || lvl[i] % 2 == 1) {
            ans += sqr(a[i].r);
        } else {
            ans -= sqr(a[i].r);
        }
    }

    printf("%.10lf\n", ans * pi);
}
