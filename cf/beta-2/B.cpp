#include <bits/stdc++.h>
using namespace std;

const int INF = 1234567890;

int main() {
    int n;
    scanf("%d", &n);

    vector<vector<int>> cnt2(n, vector<int>(n));
    vector<vector<int>> cnt5(n, vector<int>(n));
    int zi = -1, zj = -1;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int x;
            scanf("%d", &x);
            if (x == 0) zi = i, zj = j, cnt2[i][j] = 100, cnt5[i][j] = 100;
            while (x != 0 && x % 2 == 0) ++cnt2[i][j], x /= 2;
            while (x != 0 && x % 5 == 0) ++cnt5[i][j], x /= 5;
        }
    }

    vector<vector<int>> dp2(n, vector<int>(n, INF)), dp5(n, vector<int>(n, INF));
    vector<vector<char>> p2(n, vector<char>(n, -1)), p5(n, vector<char>(n, -1));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == 0 && j == 0) {
                dp2[i][j] = cnt2[i][j];
                dp5[i][j] = cnt5[i][j];
            } else if (i == 0) {
                dp2[i][j] = dp2[i][j - 1] + cnt2[i][j];
                dp5[i][j] = dp5[i][j - 1] + cnt5[i][j];
                p2[i][j] = 'R';
                p5[i][j] = 'R';
            } else if (j == 0) {
                dp2[i][j] = dp2[i - 1][j] + cnt2[i][j];
                dp5[i][j] = dp5[i - 1][j] + cnt5[i][j];
                p2[i][j] = 'D';
                p5[i][j] = 'D';
            } else {
                if (dp2[i][j] > dp2[i - 1][j] + cnt2[i][j]) {
                    dp2[i][j] = dp2[i - 1][j] + cnt2[i][j];
                    p2[i][j] = 'D';
                }
                if (dp2[i][j] > dp2[i][j - 1] + cnt2[i][j]) {
                    dp2[i][j] = dp2[i][j - 1] + cnt2[i][j];
                    p2[i][j] = 'R';
                }
                if (dp5[i][j] > dp5[i - 1][j] + cnt5[i][j]) {
                    dp5[i][j] = dp5[i - 1][j] + cnt5[i][j];
                    p5[i][j] = 'D';
                }
                if (dp5[i][j] > dp5[i][j - 1] + cnt5[i][j]) {
                    dp5[i][j] = dp5[i][j - 1] + cnt5[i][j];
                    p5[i][j] = 'R';
                }
            }
        }
    }

    auto& dp = dp2;
    auto& p = p2;
    if (dp[n - 1][n - 1] > dp5[n - 1][n - 1]) dp = dp5, p = p5;
    if (zi != -1 && dp[n - 1][n - 1] > 1) {
        printf("1\n");
        for (int i = 0; i < zi; ++i) putchar('D');
        for (int j = 0; j < zj; ++j) putchar('R');
        for (int i = zi; i < n - 1; ++i) putchar('D');
        for (int j = zj; j < n - 1; ++j) putchar('R');
        puts("");
    } else {
        printf("%d\n", dp[n - 1][n - 1]);
        string ans;
        int i = n - 1, j = n - 1;
        while (p[i][j] != -1) {
            ans += p[i][j];
            if (p[i][j] == 'D') {
                --i;
            } else {
                --j;
            }
        }
        reverse(ans.begin(), ans.end());
        printf("%s\n", ans.c_str());
    }
}
