#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

using ll = long long;

const int INF = 1e5;

int main() {
#if __APPLE__
    //freopen("C.in", "r", stdin);
    //freopen("C.out", "w", stdout);
#endif

    int n, m;
    while (cin >> n >> m) {
        vector<string> a(n);
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
        }

        int ans = INF * 3;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i == j) continue;
                for (int k = 0; k < n; ++k) {
                    if (k == i || k == j) continue;
                    int dig = INF;
                    for (int t = 0; t < m; ++t) {
                        if ('0' <= a[i][t] && a[i][t] <= '9') {
                            dig = min(dig, min(t, m - t));
                        }
                    }
                    int buk = INF;
                    for (int t = 0; t < m; ++t) {
                        if ('a' <= a[j][t] && a[j][t] <= 'z') {
                            buk = min(buk, min(t, m - t));
                        }
                    }
                    int sim = INF;
                    for (int t = 0; t < m; ++t) {
                        if (a[k][t] == '#' || a[k][t] == '*' || a[k][t] == '&') {
                            sim = min(sim, min(t, m - t));
                        }
                    }
                    ans = min(ans, dig + buk + sim);
                }
            }
        }
        cout << ans << endl;
    }
}
