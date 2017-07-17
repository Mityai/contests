#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

using ll = long long;

int main() {
#if __APPLE__
    //freopen("A.in", "r", stdin);
    //freopen("A.out", "w", stdout);
#endif

    int t;
    scanf("%d", &t);

    for (int i = 0; i < t; ++i) {
        int k, x, y;
        scanf("%d%d%d", &k, &x, &y);
        if (x < y) swap(x, y);
        int ans = 0;
        while (x < k || abs(x - y) < 2) {
            ++ans;
            ++x;
        }
        printf("%d\n", ans);
    }
}
