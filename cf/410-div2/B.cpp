#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

const int INF = 1e9;

int main() {
#if __APPLE__
    freopen("B.in", "r", stdin);
    freopen("B.out", "w", stdout);
#endif

    ios_base::sync_with_stdio(false);

    int n;
    cin >> n;

    vector<string> a(n);
    int m;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        m = a[i].size();
        a[i] += a[i];
    }

    int ans = INF;
    for (int i = 0; i < m; ++i) {
        string need = a[0].substr(i, m);
        int cur = 0;
        bool can = true;
        for (int j = 0; j < n; ++j) {
            bool ok = false;
            for (int k = 0; k < m; ++k) {
                if (a[j].substr(k, m) == need) {
                    cur += k;
                    ok = true;
                    break;
                }
            }
            if (!ok) {
                can = false;
            }
        }
        if (can) {
            ans = min(ans, cur);
        }
    }

    if (ans == INF) cout << -1 << endl;
    else cout << ans << endl;
}
