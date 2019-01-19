#include <bits/stdc++.h>
using namespace std;

#define eprintf(...) fprintf(stderr, __VA_ARGS__)

int main() {
#if __APPLE__
    // freopen("A.in", "r", stdin);
    // freopen("A.out", "w", stdout);
#endif

    int n;
    scanf("%d", &n);

    int ans = 0;
    while (n > 0) {
        bool ok = false;
        for (int k = 1; k <= 30; ++k) {
            int m = 1u << k;
            int r = n % m;
            if (r > (1u << (k - 1))) {
                n /= m;
                ++ans;
                ok = true;
                break;
            }
        }
        if (!ok) {
            break;
        }
    }

    printf("%d\n", ans);
}
