#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

const ll INF = 1e15;
const int N = 2000;

vector<pair<int, int>> a[N + 1];

int main() {
#if __APPLE__
    freopen("D.in", "r", stdin);
    freopen("D.out", "w", stdout);
#endif

    int n;
    scanf("%d", &n);

    for (int i = 1; i <= n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            int x;
            scanf("%d", &x);
            a[i].push_back({x, j});
            a[j].push_back({x, i});
        }
    }

    for (int i = 1; i <= n; ++i) {
        sort(a[i].begin(), a[i].end());
    }

    for (int s = 1; s <= n; ++s) {
        ll ans = INF;
        for (auto& to : a[s]) {
            int w = to.fi;
            int u = to.se;
            auto mn = a[u][0];
            if (mn.second == s) {
                mn = a[u][1];
            }
            ll we = min(w, mn.first);
            ans = min({ans, (n - 2) * 1ll * we + w, (n - 1) * 1ll * w});
        }
        printf("%lld\n", ans);
    }
}
