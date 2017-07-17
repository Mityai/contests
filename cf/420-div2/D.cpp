#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

const int INF = 1e9;

typedef long long ll;

const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, -1, 0, 1};

int main() {
#if __APPLE__
    freopen("D.in", "r", stdin);
    freopen("D.out", "w", stdout);
#endif

    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);

    vector<set<int>> rw(n + 1), cl(m + 1);
    for (int i = 0; i < k; ++i) {
        int r, c;
        scanf("%d%d", &r, &c);
        rw[r].insert(c);
        cl[c].insert(r);
    }

    map<pair<int, int>, int> dist;

    dist[{1, 1}] = 0;
    deque<pair<int, int>> q;
    q.push_back({1, 1});

    int ans = INF;
    while (!q.empty()) {
        auto v = q.front();
        int i = v.fi;
        int j = v.se;
        q.pop_front();

        if (rw[i].find(j) == rw[i].end()) continue;
        cl[j].erase(i);
        rw[i].erase(j);

        queue<pair<int, int>> p;
        p.push({i, j});
        while (!p.empty()) {
            int x = p.front().fi;
            int y = p.front().se;
            p.pop();
            if (x != i || y != j) {
                q.push_front({x, y});
            }
            for (int t = 0; t < 4; ++t) {
                int new_i = x + dx[t];
                int new_j = y + dy[t];
                if (1 <= new_i && new_i <= n) {
                    if (1 <= new_j && new_j <= m) {
                        if (rw[new_i].find(new_j) != rw[new_i].end()) {
                            if (dist.find({new_i, new_j}) == dist.end() ||
                                dist[{new_i, new_j}] > dist[{i, j}]) {
                                dist[{new_i, new_j}] = dist[{i, j}];
                                p.push({new_i, new_j});
                            }
                        }
                    }
                }
            }
        }

        for (int ki = max(1, i - 2); ki <= min(n, i + 2); ++ki) {
            if (ki == n && abs(ki - i) <= 1) {
                ans = min(ans, dist[{i, j}] + 1);
            }
            for (int new_j : rw[ki]) {
                int new_i = ki;
                if (dist.find({new_i, new_j}) == dist.end() ||
                    dist[{new_i, new_j}] > dist[{i, j}] + 1) {
                    dist[{new_i, new_j}] = dist[{i, j}] + 1;
                    q.push_back({new_i, new_j});
                }
            }
        }
        for (int kj = max(1, j - 2); kj <= min(m, j + 2); ++kj) {
            if (kj == m && abs(kj - j) <= 1) {
                ans = min(ans, dist[{i, j}] + 1);
            }
            for (int new_i : cl[kj]) {
                int new_j = kj;
                if (dist.find({new_i, new_j}) == dist.end() ||
                    dist[{new_i, new_j}] > dist[{i, j}] + 1) {
                    dist[{new_i, new_j}] = dist[{i, j}] + 1;
                    q.push_back({new_i, new_j});
                }
            }
        }
    }

    if (dist.find({n, m}) != dist.end()) {
        ans = min(ans, dist[{n, m}]);
    }

    if (ans == INF) {
        ans = -1;
    }

    printf("%d\n", ans);
}
