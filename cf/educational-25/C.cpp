#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    scanf("%d%d", &n, &k);

    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &a[i]);
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            if (a[i] < a[j]) swap(a[i], a[j]);
        }
    }

    int ans = 0;
    for (int i = 0; i < n; ++i) {
        while (2 * k < a[i]) {
            ++ans;
            k *= 2;
        }
        k = max(k, a[i]);
    }

    printf("%d\n", ans);
}
