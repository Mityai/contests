#include <bits/stdc++.h>
using namespace std;

#define eprintf(...) fprintf(stderr, __VA_ARGS__)

using ull = unsigned long long;

int main() {
#if __APPLE__
    // freopen("B.in", "r", stdin);
    // freopen("B.out", "w", stdout);
#endif

    int n;
    scanf("%d", &n);

    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &a[i]);
    }

    for (int i = 1; i < n; ++i) {
        if (a[i] == 0 && a[i - 1] != 0) {
            puts("-1");
            return 0;
        }
    }

    ull ans = 0;
    ull ansprev = 0;
    for (int i = 1; i < n; ++i) {
        int l = a[i - 1], r = a[i];
        ull cnt = 0;
        if (l > r) {
            while (l > r) {
                r *= 2;
                ++cnt;
            }
            cnt += ansprev;
            ans += cnt;
        } else {
            bool ok = false;
            ull j = 0;
            for (; j < ansprev; ++j) {
                l *= 2;
                if (l > r) {
                    ok = true;
                    break;
                }
            }
            if (ok) {
                cnt = ansprev - j;
                ans += cnt;
            }
        }
        ansprev = cnt;
    }

    printf("%llu\n", ans);
}
