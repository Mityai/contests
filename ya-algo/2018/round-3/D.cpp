#include <bits/stdc++.h>
using namespace std;

const double INF = 1e9;

using interval = pair<double, double>;

interval intersect(const interval& a, const interval& b) {
    return {max(a.first, b.first), min(a.second, b.second)};
}

interval wide(const interval& a, double m) {
    return {a.first - m, a.second + m};
}

bool ok(double m, const vector<int>& x, vector<char> mark, const vector<vector<int>>& g) {
    int n = x.size();
    vector<interval> intervals(n);
    queue<int> q;
    for (int i = 0; i < n; ++i) {
        if (mark[i] == 1) {
            intervals[i] = {x[i], x[i]};
            for (int u : g[i]) {
                if (mark[u] == 0) {
                    q.push(u);
                    mark[u] = 2;
                } else if (mark[u] == 1) {
                    if (fabs(x[i] - x[u]) > m) {
                        return false;
                    }
                }
            }
        } else {
            intervals[i] = {-INF, +INF};
        }
    }

    while (!q.empty()) {
        int v = q.front();
        q.pop();
        mark[v] = 1;
        for (int u : g[v]) {
            if (mark[u] == 1) {
                intervals[v] = intersect(intervals[v], wide(intervals[u], m));
            } else {
                q.push(u);
                mark[u] = 2;
            }
        }
    }

    for (int v = 0; v < n; ++v) {
        if (intervals[v].first > intervals[v].second) {
            return false;
        }
    }
    return true;
}

int main() {
    int n;
    scanf("%d", &n);

    vector<int> x(n);
    vector<char> mark(n);
    for (int i = 0; i < n; ++i) {
        char s[8];
        scanf(" %s", s);
        if (s[0] != '*') {
            mark[i] = true;
            x[i] = atoi(s);
        }
    }

    vector<vector<int>> g(n);
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        --u, --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }


    double lb = 0, rb = 1e9;
    for (int iter = 0; iter < 100; ++iter) {
        double mb = (lb + rb) / 2;
        if (ok(mb, x, mark, g)) {
            rb = mb;
        } else {
            lb = mb;
        }
    }

    printf("%.10lf\n", rb);
}
