#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    scanf("%d%d", &n, &m);

    int ds, cs;
    scanf("%d%d", &ds, &cs);

    int da, ca;
    scanf("%d%d", &da, &ca);

    vector<int> h(n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &h[i]);
    }

    sort(h.begin(), h.end());

    int ans = 0;
    for (int i = 0; i <= 100; ++i) {
        int mp = m - i * ca;
        if (mp < 0) {
            break;
        }
        auto b = h;
        int killed = 0;
        for (int k = 0; k < n; ++k) {
            b[k] -= i * da;
            if (b[k] <= 0) {
                ++killed;
            } else {
                int need = (b[k] + ds - 1) / ds;
                mp -= need * cs;
                if (mp < 0) {
                    break;
                }
                ++killed;
            }
        }
        ans = max(ans, killed);
    }

    printf("%d\n", ans);
}
