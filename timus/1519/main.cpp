#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long long ull;

const int N = 12;

int n, m;
char s[N][N + 1];

int get3(int prev, int cur) {
    int inter = (prev ^ cur);
    int dble = (prev & cur);
    int ret = 0;
    for (int i = m - 1; i >= 0; --i) {
        int x = ((inter >> i) & 1);
        int y = 2 * ((dble >> i) & 1);
        ret = ret * 3 + x + y;
    }
    int p = 0;
    for (int i = 0, q = 0; i < m; ++i) {
        int x = (q | ((prev >> i) & 1));
        p |= (x << i);
        q ^= ((prev >> i) & 1);
    }
    bool ok = false;
    for (int i = 0, q = 0; i < m; ++i) {
        int x = (q | ((cur >> i) & 1));
        if ((p >> i) & x) {
            ok = true;
            break;
        }
        q ^= ((cur >> i) & 1);
    }
    if (!ok) {
        ret = 1;
    }
    return ret;
}

int main() {
    scanf("%d%d", &n, &m);

    vector<int> blocks(n);
    for (int i = 0; i < n; ++i) {
        scanf(" %s", s[i]);
        for (int j = 0; j < m; ++j) {
            blocks[i] |= (1 << j) * (s[i][j] == '*');
        }
    }

    int pw3 = 1;
    for (int i = 0; i < m; ++i) {
        pw3 *= 3;
    }

    vector<char> good(pw3, true);
    for (int mask = 0; mask < pw3; ++mask) {
        int f = mask;
        for (int i = 0, q = 0; i < m; ++i) {
            int x = f % 3;
            if (i == 0 && x == 0) {
                good[mask] = false;
                break;
            }
            if (i == m - 1 && x == 0) {
                good[mask] = false;
                break;
            }
            if (x == 0 && q == 0) {
                good[mask] = false;
                break;
            }
            if (q == 1 && x == 2) {
                good[mask] = false;
                break;
            }
            q = (q + x) % 2;
            f /= 3;
        }
    }

    vector<vector<int>> good_prev(1 << m);
    for (int cur = 0; cur < (1 << m); ++cur) {
        for (int prev = 0; prev < (1 << m); ++prev) {
            if (good[get3(prev, cur)]) {
                good_prev[cur].push_back(prev);
            }
        }
    }

    vector<vector<int>> masks(n);
    for (int i = 0; i < n; ++i) {
        for (int mask = 1; mask < (1 << m); ++mask) {
            int cnt = __builtin_popcount(mask);
            if (cnt & 1) continue;
            bool ok = true;
            for (int j = 0; j < m; ++j) {
                if ((mask >> j) & 1) {
                    if (s[i][j] == '*' || i + 1 == n || s[i + 1][j] == '*') {
                        ok = false;
                        break;
                    }
                }
            }
            if (ok) {
                masks[i].push_back(mask);
            }
        }
    }
    masks[n - 1].push_back(0);

    vector<vector<ull>> dp(n, vector<ull>(1 << m));
    for (int mask : masks[0]) {
        dp[0][mask] = 1;
    }
    for (int i = 1; i < n; ++i) {
        for (int cur : masks[i]) {
            vector<int> prevs;
            /*if (good_prev[cur].size() < masks[i - 1].size()) {
                for (int prev : good_prev[cur]) {
                    if ((prev ^ blocks[i - 1]) == (prev | blocks[i - 1])) {
                        prevs.push_back(prev);
                    }
                }
            } else {*/
                for (int prev : masks[i - 1]) {
                    if (good[get3(cur, prev)]) {
                        prevs.push_back(prev);
                    }
                }
            //}
            for (int prev : prevs) {
                dp[i][cur] += dp[i - 1][prev];
            }
        }
    }
    ull ans = 0;
    for (int cur : masks[n - 2]) {
        for (int prev : masks[n - 2]) {
            if (good[get3(cur, prev)]) {
                ans += dp[n - 2][prev];
            }
        }
    }

    printf("%llu\n", ans);
}
