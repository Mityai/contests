#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

int main() {
    size_t n, m;
    cin >> n >> m;

    vector<string> a(n);
    for (size_t row = 0; row < n; ++row) {
        cin >> a[row];
    }

    reverse(a.begin(), a.end());

    vector<vector<vector<int>>> fastest(n, vector<vector<int>>(2, vector<int>(2, INF)));
    int last_row = 0;
    for (size_t row = 0; row < n; ++row) {
        int most_left = m + 1;
        int most_right = 0;
        for (size_t i = 0; i < m + 2; ++i) {
            if (a[row][i] == '1') {
                last_row = row;
                if (most_left == m + 1)
                    most_left = i;
                most_right = i;
            }
        }
        fastest[row][0][0] = 2 * most_right;
        fastest[row][1][1] = 2 * (m + 1 - most_left);
        fastest[row][0][1] = m + 1;
        fastest[row][1][0] = m + 1;
    }

    vector<vector<int>> dp(n, vector<int>(2, INF));
    dp[0][0] = 0;
    for (size_t row = 0; row + 1 < n; ++row) {
        dp[row + 1][0] = min(dp[row][0] + fastest[row][0][0],
                             dp[row][1] + fastest[row][1][0]) + 1;
        dp[row + 1][1] = min(dp[row][0] + fastest[row][0][1],
                             dp[row][1] + fastest[row][1][1]) + 1;
    }
    int most_left = m + 1, most_right = 0;
    for (size_t col = 0; col < m + 2; ++col) {
        if (a[last_row][col] == '1') {
            if (most_left == m + 1)
                most_left = col;
            most_right = col;
        }
    }
    int ans = min(dp[last_row][0] + most_right, dp[last_row][1] + (int(m) + 1 - most_left));
    printf("%d\n", ans);
}
