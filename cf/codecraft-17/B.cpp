#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

using ll = long long;

int main() {
#if __APPLE__
    freopen("B.in", "r", stdin);
    freopen("B.out", "w", stdout);
#endif

    const int N = 1e5 + 123;

    int n;
    scanf("%d", &n);

    vector<int> cnt(N);
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        for (ll p = 2; p * p <= a[i]; ++p) {
            if (a[i] % p == 0) {
                cnt[p]++;
            }
            while (a[i] % p == 0) a[i] /= p;
        }
        if (a[i] != 1) cnt[a[i]]++;
    }

    int ans = 1;
    for (int i = 0; i < N; i++) {
        ans = max(ans, cnt[i]);
    }

    printf("%d\n", ans);
}
    
