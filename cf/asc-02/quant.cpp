#include <bits/stdc++.h>
using namespace std;

const int INF = 1234567890;

int main() {
    freopen("quant.in", "r", stdin);
    freopen("quant.out", "w", stdout);

    int n;
    scanf("%d", &n);

    vector<int> x(n + 1);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &x[i]);
    }

    int m, s;
    scanf("%d%d", &m, &s);

    vector<vector<int>> lvls(m, vector<int>(s));
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < s; ++j) {
            scanf("%d", &lvls[i][j]);
        }
    }

    vector<vector<int>> dp(n + 1, vector<int>(m, INF));
    vector<vector<int>> plvl(n + 1, vector<int>(m, -1));
    vector<vector<int>> ptook(n + 1, vector<int>(m, -1));
    dp[0][0] = 0;
    for (int i = 1; i <= n; ++i) {
        for (int lvl = 0; lvl < m; ++lvl) {
            for (int want = 0; want < s; ++want) {
                int diff = abs(lvls[lvl][want] - x[i]);
                int to = want & (m - 1);
                if (dp[i][to] > dp[i - 1][lvl] + diff) {
                    dp[i][to] = dp[i - 1][lvl] + diff;
                    plvl[i][to] = lvl;
                    ptook[i][to] = want;
                }
            }
        }
    }

    int lvl = 0;
    for (int i = 0; i < m; ++i) {
        if (dp[n][lvl] > dp[n][i]) {
            lvl = i;
        }
    }
    printf("%d\n", dp[n][lvl]);
    int item = n;
    vector<int> ans;
    while (item != 0) {
        ans.push_back(ptook[item][lvl]);
        lvl = plvl[item][lvl];
        --item;
    }
    reverse(ans.begin(), ans.end());
    for (int x : ans) {
        printf("%d ", x);
    }
    puts("");
}
