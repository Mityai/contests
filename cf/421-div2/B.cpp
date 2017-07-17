#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

const double pi = acos(-1);

int main() {
#if __APPLE__
    //freopen("B.in", "r", stdin);
    //freopen("B.out", "w", stdout);
#endif

    int n, a;
    scanf("%d%d", &n, &a);

    double ang = (n - 2) * pi / n;
    double bestdeg = 1e8;
    int ans = n;
    for (int i = n; i >= 3; --i) {
        double cur = ang / (n - 2) * (n - i + 1);
        double deg = cur / pi * 180;
        if (fabs(deg - a) < fabs(bestdeg - a)) {
            ans = i;
            bestdeg = deg;
        }
    }

    printf("%d %d %d\n", 1, 2, ans);
}
