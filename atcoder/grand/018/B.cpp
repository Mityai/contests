#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

pair<int, int> get_max(const vector<vector<int>>& a, const vector<char>& used) {
    vector<int> took(a[0].size());
    for (int i = 0; i < a.size(); ++i) {
        for (int j = 0; j < a[i].size(); ++j) {
            if (used[a[i][j]]) {
                ++took[a[i][j]];
                break;
            }
        }
    }
    int mx_id = -1, mx = -1;
    for (int i = 0; i < took.size(); ++i) {
        if (mx < took[i]) {
            mx = took[i];
            mx_id = i;
        }
    }
    return {mx_id, mx};
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);

    vector<vector<int>> a(n, vector<int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            scanf("%d", &a[i][j]);
            --a[i][j];
        }
    }

    int ans = INF;
    vector<char> used(m, true);
    for (int i = 0; i < m; ++i) {
        auto res = get_max(a, used);
        used[res.first] = false;
        ans = min(ans, res.second);
    }

    printf("%d\n", ans);
}
