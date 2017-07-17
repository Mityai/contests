#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

using ll = long long;

const int N = 1e7;

vector<int> g[N + 1];
int have[N + 1];
int nxt[N + 1];
int over[N + 1];

int main() {
#if __APPLE__
    freopen("D.in", "r", stdin);
    freopen("D.out", "w", stdout);
#endif

    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);

    for (int i = 0; i < n; ++i) {
        int x;
        scanf("%d", &x);
        ++have[x];
    }

    int carry = 0;
    for (int t = N, nx = N + 1; t >= 0; --t) {
        carry += max(0, have[t] - k);
        have[t] = min(have[t], k);
        nxt[t] = nx;
        if (have[t] < k) {
            over[t] = min(k - have[t], carry);
            have[t] += over[t];
            carry -= over[t];
            if (over[t] > 0) {
                nx = t;
            }
        }
    }

    if (carry > 0) {
        puts("-1");
        return 0;
    }

    vector<pair<int, int>> tobuy(m);
    for (int i = 0; i < m; ++i) {
        scanf("%d", &tobuy[i].fi);
        tobuy[i].se = i;
    }

    sort(tobuy.begin(), tobuy.end(),
            [](pair<int, int>& p1, pair<int, int>& p2) {
                return p1.fi < p2.fi;
            });

    vector<int> ans;
    for (int t = 0, j = 0; t <= N; ++t) {
        while (j < m && tobuy[j].fi < t) ++j;
        int added = 0;
        for (int i = 0; i < k - have[t] && j < m; ++i, ++j) {
            ans.push_back(tobuy[j].se);
            ++added;
        }
        have[t] += added;
        if (have[t] < k) {
            int can = k - have[t];
            int x = nxt[t];
            while (x != N + 1 && can > 0) {
                int cur = min(can, over[x]);
                over[x] -= cur;
                have[x] -= cur;
                can -= cur;
                x = nxt[x];
            }
        }
    }

    printf("%d\n", int(ans.size()));
    for (int x : ans) {
        printf("%d ", x + 1);
    }
    puts("");
}
