#include <bits/stdc++.h>
using namespace std;

int main() {
    const int MOD = 1e9 + 7;

    int n;
    scanf("%d", &n);

    int ans = 1;
    for (int i = 1; i <= (n - 1) * (n - 1); ++i) {
        ans = (ans * 1ll * n) % MOD;
    }

    printf("%d\n", ans);
}
