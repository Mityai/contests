#include <bits/stdc++.h>
using namespace std;

int main() {
    freopen("ksort.in", "r", stdin);
    freopen("ksort.out", "w", stdout);

    int n, k;
    scanf("%d%d", &n, &k);

    int a[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", a + i);
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (a[i] < a[j] && a[i] % k == a[j] % k) {
                swap(a[i], a[j]);
            }
        }
    }

    for (int i = 1; i < n; i++) {
        if (a[i - 1] > a[i]) {
            puts("NO");
            return 0;
        }
    }

    puts("YES");
}
