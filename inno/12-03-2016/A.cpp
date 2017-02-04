#include <bits/stdc++.h>
using namespace std;

int main() {
#if __APPLE__
    freopen("A.in", "r", stdin);
    freopen("A.out", "w", stdout);
#endif

    int L, T, vA, vB;
    scanf("%d%d%d%d", &L, &T, &vA, &vB);

    int n;
    scanf("%d", &n);

    bool stopA[T + 1], stopB[T + 1];
    memset(stopA, 0, sizeof stopA);
    memset(stopB, 0, sizeof stopB);

    for (int i = 0; i < n; i++) {
        int type, t, d;
        scanf("%d%d%d", &type, &t, &d);
        for (int j = t; j < t + d; j++) {
            if (type == 1) stopA[j] = true;
            else stopB[j] = true;
        }
    }

    int ans = 0;
    for (int i = 0, curA = 0, curB = 0; i <= T; i++) {
        if (i > 0) {
            int prevA = curA;
            if (!stopA[i - 1]) prevA -= vA;
            int prevB = curB;
            if (!stopB[i - 1]) prevB += vB;
            if (prevA < prevB && curA >= curB) {
                ans++;
            } else if (prevA > prevB && curA <= curB) {
                ans++;
            }
        }
        if (!stopA[i]) {
            curA = (curA + vA) % L;
        }
        if (!stopB[i]) {
            curB = (curB - vB + L) % L;
        }
    }

    printf("%d\n", ans);
}
