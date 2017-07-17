#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

using ll = long long;

int main() {
#if __APPLE__
    //freopen("A.in", "r", stdin);
    //freopen("A.out", "w", stdout);
#endif

    int n;
    scanf("%d", &n);

    int a[n];
    for (int i = 0; i < n; ++i) {
        scanf("%d", &a[i]);
    }

    sort(a, a + n);

    int ans = 0;
    for (int i = 0; i < n; ++i) {
        if (a[i] > a[0] && a[i] < a[n - 1]) {
            ++ans;
        }
    }

    printf("%d\n", ans);
}
