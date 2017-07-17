#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

const int INF = int(1e9) + 8;

int max_score(ll solved, ll n) {
    if (n < 2 * solved && solved <= n) {
        return 500;
    }
    if (n < 4 * solved && 2 * solved <= n) {
        return 1000;
    }
    if (n < 8 * solved && 4 * solved <= n) {
        return 1500;
    }
    if (n < 16 * solved && 8 * solved <= n) {
        return 2000;
    }
    if (n < 32 * solved && 16 * solved <= n) {
        return 2500;
    }
    if (0 <= solved && 32 * solved <= n) {
        return 3000;
    }
}

pair<int, int> get(ll solved, ll part, int vasya, int petya) {
    int max_sc = max_score(solved, part);
    int score_vasya = 0, score_petya = 0;
    if (vasya != -1) {
        score_vasya = max_sc - max_sc / 250 * vasya;
    }
    if (petya != -1) {
        score_petya = max_sc - max_sc / 250 * petya;
    }
    return {score_vasya, score_petya};
}

int main() {
#if __APPLE__
    freopen("B.in", "r", stdin);
    freopen("B.out", "w", stdout);
#endif

    int n;
    while (scanf("%d", &n) == 1) {

    vector<int> solved(5);
    vector<vector<int>> a(2, vector<int>(5));
    for (int i = 0; i < n; ++i) {
        vector<int> b(5);
        for (int j = 0; j < 5; ++j) {
            scanf("%d", &b[j]);
            if (b[j] != -1) {
                ++solved[j];
            }
        }
        if (i < 2) {
            a[i] = b;
        }
    }

    ll ans = -1;
    for (ll mb = 0; mb <= 4000; ++mb) {
        ll part = n + mb;
        ll res1 = 0, res2 = 0;
        for (int task = 0; task < 5; ++task) {
            ll mx = max_score(solved[task], part);
            auto sc = get(solved[task], part, a[0][task], a[1][task]);
            if (a[0][task] != -1) {
                for (ll max_sc = 500; max_sc <= mx; max_sc += 500) {
                    ll l = -1, r = mb + 1;
                    while (l + 1 < r) {
                        ll m = (l + r) / 2;
                        if (max_sc < max_score(solved[task] + m, part)) {
                            l = m;
                        } else {
                            r = m;
                        }
                    }
                    if (max_score(solved[task] + r, part) != max_sc || r == mb + 1) {
                        continue;
                    }
                    auto sc_cur = get(solved[task] + r, part, a[0][task], a[1][task]);
                    if (sc.fi - sc.se < sc_cur.fi - sc_cur.se) {
                        sc = sc_cur;
                    }
                }
            }
            res1 += sc.fi;
            res2 += sc.se;
        }

        if (res1 > res2) {
            ans = mb;
            break;
        }
    }
    printf("%lld\n", ans);
    }
}
