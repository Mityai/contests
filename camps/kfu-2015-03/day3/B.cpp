#include <bits/stdc++.h>
using namespace std;

int main() {
    freopen("metro.in", "r", stdin);
    freopen("metro.out", "w", stdout);

    int n;
    scanf("%d", &n);

    int a[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    int right[n];
    memset(right, -1, sizeof right);

    for (int i = n - 1; i >= 0; i--) {
        if (a[i] == 1) {
            right[i] = i;
        } else if (i < n - 1) {
            right[i] = right[i + 1];
        }
    }

    if (right[0] == -1) {
        puts("1");
        return 0;
    }

    int ans, len = -1;
    for (int i = 0, left = -1; i < n; i++) {
        if (a[i] == 1) left = i;
        else {
            int d = min(i - left, right[i] - i);
            if (left == -1) d = right[i] - i;
            if (right[i] == -1) d = i - left;
            if (d > len) {
                len = d;
                ans = i;
            }
        }
    }

    printf("%d\n", ans + 1);
}
