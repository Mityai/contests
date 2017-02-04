#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

using ll = long long;

int main() {
#if __APPLE__
    //freopen(".in", "r", stdin);
    //freopen(".out", "w", stdout);
#endif

    int n, k;
    cin >> n >> k;

    int ans = 0;
    int t = 0;
    for (int i = 1; i <= n; i++) {
        if (t + i * 5 + k > 240) {
            break;
        }
        t += i * 5;
        ++ans;
    }
    cout << ans << endl;
}
