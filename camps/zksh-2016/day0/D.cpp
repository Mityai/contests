#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

const ll INF = 1e9;

int s(ll x, ll y, ll f) {
    if (x == INF || y == INF) return INF;
    if (f == 1) return x + y;
    if (f == 2) return x - y;
    if (f == 3) return x * y;
    if (f == 4 && y != 0 && x % y == 0) return x / y;
    return INF;
}

int main() {
    vector< pair<int, int> > a(4);
    for (int i = 0; i < 4; i++) {
        scanf("%d", &a[i].se);
        a[i].fi = i + 1;
    }

    ll best = a[0].se + a[1].se + a[2].se + a[3].se;
    do {
        vector<ll> b = {a[0].se, a[1].se, a[2].se, a[3].se};

        for (int i = 1; i <= 4; i++) {
            for (int j = 1; j <= 4; j++) {
                for (int k = 1; k <= 4; k++) {
                    vector<int> r = {1, 2, 3};
                    do {
                        auto g = b;
                        auto f = r;
                        for (int l = 0; l < 3; l++) {
                            if (f[l] == 1) {
                                g[l] = s(g[l], g[l + 1], i);
                                g.erase(g.begin() + l + 1);
                                f.erase(f.begin() + l);
                                break;
                            }
                        }
                        for (int l = 0; l < 2; l++) {
                            if (f[l] == 2) {
                                g[l] = s(g[l], g[l + 1], j);
                                g.erase(g.begin() + l + 1);
                                f.erase(f.begin() + l);
                                break;
                            }
                        }
                        for (int l = 0; l < 1; l++) {
                            if (f[l] == 3) {
                                g[l] = s(g[l], g[l + 1], k);
                                g.erase(g.begin() + l + 1);
                                f.erase(f.begin() + l);
                                break;
                            }
                        }

                        if (abs(g[0] - 21) < abs(best - 21)) {
                            best = g[0];
                        } else if (abs(g[0] - 21) == abs(best - 21) && g[0] < best) {
                            best = g[0];
                        }
                    } while (next_permutation(r.begin(), r.end()));
                }
            }
        }
    } while (next_permutation(a.begin(), a.end()));

    printf("%lld\n", best);
}
