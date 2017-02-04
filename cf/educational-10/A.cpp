#include <bits/stdc++.h>
using namespace std;

int main() {
#if __APPLE__
    freopen("A.in", "r", stdin);
    freopen("A.out", "w", stdout);
#endif

    int h1, h2;
    while (scanf("%d%d", &h1, &h2) == 2) {
        int a, b;
        scanf("%d%d", &a, &b);

        if (a <= b && h1 + 8 * a < h2) {
            puts("-1");
            continue;
        }

        int day = 0;
        for (int hh = 14;; hh = (hh + 1) % 24) {
            if (hh == 0) day++;
            if (10 <= hh && hh < 22) {
                h1 += a;
            } else {
                h1 -= b;
            }
            if (h1 >= h2) {
                printf("%d\n", day);
                break;
            }
        }
    }
}
