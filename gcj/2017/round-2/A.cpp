#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

int main() {
    freopen("A.in", "r", stdin);
    freopen("A.out", "w", stdout);

    int t;
    scanf("%d", &t);

    for (int test = 1; test <= t; ++test) {
        int n, p;
        scanf("%d%d", &n, &p);

        vector<int> a(p);
        for (int i = 0; i < n; ++i) {
            int x;
            scanf("%d", &x);
            ++a[x % p];
        }

        int ans = 0;
        if (p == 2) {
            ans = a[0] + (a[1] + (2 - 1)) / 2;
        } else if (p == 3) {
            int mn = min(a[1], a[2]);
            a[1] -= mn;
            a[2] -= mn;
            ans = a[0] + mn;
            ans += (a[1] + (3 - 1)) / 3;
            ans += (a[2] + (3 - 1)) / 3;
        } else if (p == 4) {
            ans = a[0];
            int mn13 = min(a[1], a[3]);
            int mn22 = a[2] / 2;
            ans += mn13;
            ans += mn22;
            a[1] -= mn13;
            a[2] %= 2;
            a[3] -= mn13;
            if (a[2] == 1) {
                ++ans;
                --a[2];
                if (a[1] > 0) {
                    a[1] = max(0, a[1] - 2);
                } else if (a[3] > 0) {
                    a[3] = max(0, a[3] - 2);
                }
            }
            ans += (a[1] + (4 - 1)) / 4;
            ans += (a[3] + (4 - 1)) / 4;
        }

        printf("Case #%d: %d\n", test, ans);
    }
}
