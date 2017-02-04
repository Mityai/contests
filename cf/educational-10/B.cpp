#include <bits/stdc++.h>
using namespace std;

int main() {
#if __APPLE__
    freopen("B.in", "r", stdin);
    freopen("B.out", "w", stdout);
#endif

    int n;
    while (scanf("%d", &n) == 1) {
        multiset<int> q;
        for (int i = 0; i < n; i++) {
            int x;
            scanf("%d", &x);
            q.insert(x);
        }

        int a[n];
        for (int i = 0; i < n; i++) {
            if (i & 1) {
                a[i] = *q.rbegin();
                q.erase(--q.end());
            } else {
                a[i] = *q.begin();
                q.erase(q.begin());
            }
        }

        bool ok = true;
        for (int i = 0; i < n; i++) {
            if (i & 1) {
                if (a[i] < a[i - 1]) ok = false;
            } else {
                if (i > 0 && a[i] > a[i - 1]) ok = false;
            }
        }

        if (!ok) {
            puts("Impossible");
        } else {
            for (int i = 0; i < n; i++) {
                printf("%d ", a[i]);
            }
            puts("");
        }
    }
}
