#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

int main() {
#if __APPLE__
    //freopen("A.in", "r", stdin);
    //freopen("A.out", "w", stdout);
#endif

    int n, k, t, d;
    cin >> n >> t >> k >> d;

    int ans1 = ((n + k - 1) / k) * t;
    int ans2 = 0;
    for (int i = 1; n > 0; ++i) {
        if (i % t == 0) {
            n = max(0, n - k);
        }
        if (i > d) {
            if ((i - d) % t == 0) {
                n = max(0, n - k);
            }
        }
        ++ans2;
    }

    if (ans1 <= ans2) {
        puts("NO");
    } else {
        puts("YES");
    }
}
