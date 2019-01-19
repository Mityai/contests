#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using row = vector<ll>;
using field = vector<row>;
using cell = pair<int, int>;

const int di[] = {-1, 0, 1, 0};
const int dj[] = {0, 1, 0, -1};
const ll INF = 1e18;

bool in(const cell& v, int n, int m) {
    return 0 <= v.first && v.first < n && 0 <= v.second && v.second < m;
}

int part(const cell& v, int si, int sj) {
    if (v.first < si && v.second < sj) {
        return 0;
    } else if (v.first < si && v.second > sj) {
        return 1;
    } else if (v.first > si && v.second > sj) {
        return 2;
    } else if (v.first > si && v.second < sj) {
        return 3;
    }
    return 5;
}

field dijkstra(int si, int sj, const field& a, const vector<char>& forb, int fi, int fj) {
    int n = a.size();
    int m = a.back().size();
    field d(n, row(m, INF));
    set<pair<ll, cell>> q;
    q.insert({d[si][sj] = a[si][sj], cell(si, sj)});
    while (!q.empty()) {
        cell v = q.begin()->second;
        q.erase(q.begin());
        for (int k = 0; k < 4; ++k) {
            cell u = v;
            u.first += di[k];
            u.second += dj[k];
            if (in(u, n, m)) {
                if (!forb[part(u, fi, fj)]) {
                    if (a[u.first][u.second] != -1) {
                        if (d[u.first][u.second] > d[v.first][v.second] + a[u.first][u.second]) {
                            q.erase({d[u.first][u.second], u});
                            d[u.first][u.second] = d[v.first][v.second] + a[u.first][u.second];
                            q.insert({d[u.first][u.second], u});
                        }
                    }
                }
            }
        }
    }
    return d;
}

int main() {
    int n, m, si, sj;
    scanf("%d%d%d%d", &n, &m, &si, &sj);

    field a(n, row(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            scanf("%lld", &a[i][j]);
        }
    }

    vector<vector<field>> d(n, vector<field>(m));
    vector<vector<field>> d2(n, vector<field>(m));
    for (int i = 0; i < si; ++i) {
        int j = sj;
        d[i][j] = dijkstra(i, j, a, {true, false, true, true, false}, si, sj);
    }
    for (int j = sj + 1; j < m; ++j) {
        int i = si;
        d[i][j] = dijkstra(i, j, a, {true, true, false, true, false}, si, sj);
    }
    for (int i = si + 1; i < n; ++i) {
        int j = sj;
        d[i][j] = dijkstra(i, j, a, {true, true, true, false, false}, si, sj);
    }
    for (int j = 0; j < sj; ++j) {
        int i = si;
        d[i][j] = dijkstra(i, j, a, {false, true, true, true, false}, si, sj);
    }
}
