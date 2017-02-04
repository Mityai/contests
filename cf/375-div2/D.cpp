#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

using ll = long long;

const int N = 50;

int n, m, k;
vector<string> a;
bool used[N][N];

const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, 1, 0, -1};

bool in(int i, int j) {
    return 0 <= i && i < n && 0 <= j && j < m;
}

int dfs(int i, int j) {
    used[i][j] = true;
    int ret = 1;
    for (int t = 0; t != 4; ++t) {
        int newi = i + dx[t];
        int newj = j + dy[t];
        if (in(newi, newj)) {
            if (a[newi][newj] == '.' && !used[newi][newj]) {
                ret += dfs(newi, newj);
            }
        } else {
            ret = -(N * N);
        }
    }
    return ret;
}

void paint(int i, int j) {
    a[i][j] = '*';
    for (int t = 0; t != 4; ++t) {
        int newi = i + dx[t];
        int newj = j + dy[t];
        if (a[newi][newj] == '.') {
            paint(newi, newj);
        }
    }
}

int main() {
#if __APPLE__
    freopen("D.in", "r", stdin);
    freopen("D.out", "w", stdout);
#endif

    cin >> n >> m >> k;
    a.resize(n);
    for (auto& x : a) {
        cin >> x;
    }

    vector< pair<int, pair<int, int>> > lake;
    for (int i = 0; i != n; ++i) {
        for (int j = 0; j != m; ++j) {
            if (!used[i][j] && a[i][j] == '.') {
                int ret = dfs(i, j);
                if (ret > 0) {
                    lake.push_back({ret, {i, j}});
                }
            }
        }
    }

    sort(lake.begin(), lake.end());
    int ans = 0;
    for (int i = 0; i != int(lake.size()) - k; ++i) {
        ans += lake[i].fi;
        paint(lake[i].se.fi, lake[i].se.se);
    }

    cout << ans << '\n';
    for (string& s : a) {
        cout << s << "\n";
    }
}
