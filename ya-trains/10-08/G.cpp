#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

using ll = long long;

int n, m, A, B;
vector<string> a;
vector<int> pos;

bool in(int i, int j) {
    return 0 <= i && i + 1 < n && 0 <= j && j < m;
}

pair<int, int> can(int i, int j, int da, int db) {
    if (da == 0 && db == 0) {
        if (a[i + 1][j] == '#') {
            return {i, j};
        } else if (in(i + 1, j) && a[i + 1][j] != '#') {
            return can(i + 1, j, da, db);
        }
        return {-1, -1};
    }
    if (da > 0) {
        if (in(i - 1, j)) {
            if (a[i - 1][j] != '#') {
                return can(i - 1, j, da - 1, db);
            }
        }
    } else {
        if (in(i, j + 1)) {
            if (a[i][j + 1] != '#') {
                return can(i, j + 1, da, db - 1);
            }
        }
    }
    return {-1, -1};
}

int main() {
#if __APPLE__
    freopen("G.in", "r", stdin);
    //freopen("G.out", "w", stdout);
#endif

    cin >> n >> m >> A >> B;

    a.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    pos.resize(m, -1);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (a[i][j] != '#' && a[i][j] != '_') {
                pos[j] = i;
            }
        }
    }

    bool dp[n][m];
    memset(dp, 0, sizeof dp);

    queue< pair<int, int> > q;
    q.push({pos[0], 0});
    dp[pos[0]][0] = true;

    while (!q.empty()) {
        auto p = q.front();
        q.pop();
        int curi = p.fi;
        int curj = p.se;
        if (curj == m - 1) continue;

        for (int da = 0; da <= A; da++) {
            for (int db = 0; db <= B; db++) {
                if (da == 0 && db == 0) continue;
                auto f = can(curi, curj, da, db);
                int gi = f.fi;
                int gj = f.se;
                bool ok = true;
                for (int i = curj + 1; i < gj; i++) {
                    if (pos[i] != -1) {
                        ok = false;
                    }
                }
                if (!ok) continue;
                if (gi != -1 && gj != -1) {
                    if (pos[gj] == -1 || pos[gj] == gi) {
                        if (dp[gi][gj] != true) {
                            dp[gi][gj] = true;
                            q.push({gi, gj});
                        }
                    }
                }
            }
        }
    }

    if (dp[pos[m - 1]][m - 1]) {
        puts("YES");
    } else {
        puts("NO");
    }
}
