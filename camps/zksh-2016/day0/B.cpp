#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, k;
    scanf("%d%d", &n, &k);

    if (k == 0) {
        cout << 0 << endl;
        return;
    }

    if (n == k) {
        cout << n / 2 + n % 2 << endl;
        return;
    }

    int cnt1 = k, cnt2 = 0;
    int ans = 0;
    for (int i = n; i >= 1; i--) {
        if (i <= k) {
            cnt1--;
            ans++;
        } else {
            cnt2++;
            ans += 2;
        }
        if (cnt1 == cnt2) {
            cout << ans << endl;
            return;
        }
    }
}

int main() {
    int t;
    scanf("%d", &t);

    for (int i = 0; i < t; i++) {
        solve();
    }
}
