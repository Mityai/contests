#include <bits/stdc++.h>
using namespace std;

inline int readInt() {
    char c = getchar();
    while (c <= 32) c = getchar();
    int ret = 0;
    while ('0' <= c && c <= '9') ret = ret * 10 + c - '0', c = getchar();
    return ret;
}

int main() {
    int n = readInt();
    int a[n];
    for (int i = 0; i < n; i++) {
        a[i] = readInt();
    }

    int b[n];
    for (int i = 0; i < n; i++) {
        b[i] = readInt();
    }

    int d[n];
    for (int i = 0; i < n; i++) {
        d[i] = (b[i] - a[i] + 4) & 3;
    }

    vector<int> c(1, d[0]);
    c.reserve(n + 2);
    for (int i = 1; i < n; i++) {
        if (d[i - 1] != d[i]) c.push_back(d[i]);
    }
    n = (int)c.size();

    int dp[n][n][4];
    memset(dp, 34, sizeof dp);

    for (int i = 0; i < n; i++) {
        for (int col = 0; col < 4; col++) {
            dp[i][i][col] = (c[i] - col + 4) & 3;
        }
    }

    for (int l = 1; l < n; l++) {
        for (int i = 0; i + l < n; i++) {
            int j = i + l;
            for (int k = i; k < j; k++) {
                if (dp[i][j][0] > dp[i][k][0] + dp[k + 1][j][0]) dp[i][j][0] = dp[i][k][0] + dp[k + 1][j][0];
                if (dp[i][j][1] > dp[i][k][1] + dp[k + 1][j][1]) dp[i][j][1] = dp[i][k][1] + dp[k + 1][j][1];
                if (dp[i][j][2] > dp[i][k][2] + dp[k + 1][j][2]) dp[i][j][2] = dp[i][k][2] + dp[k + 1][j][2];
                if (dp[i][j][3] > dp[i][k][3] + dp[k + 1][j][3]) dp[i][j][3] = dp[i][k][3] + dp[k + 1][j][3];
            }
            if (dp[i][j][0] > dp[i][j][1] + 1) dp[i][j][0] = dp[i][j][1] + 1;
            if (dp[i][j][0] > dp[i][j][2] + 2) dp[i][j][0] = dp[i][j][2] + 2;
            if (dp[i][j][0] > dp[i][j][3] + 3) dp[i][j][0] = dp[i][j][3] + 3;

            if (dp[i][j][1] > dp[i][j][0] + 3) dp[i][j][1] = dp[i][j][0] + 3;
            if (dp[i][j][1] > dp[i][j][2] + 1) dp[i][j][1] = dp[i][j][2] + 1;
            if (dp[i][j][1] > dp[i][j][3] + 2) dp[i][j][1] = dp[i][j][3] + 2;

            if (dp[i][j][2] > dp[i][j][0] + 2) dp[i][j][2] = dp[i][j][0] + 2;
            if (dp[i][j][2] > dp[i][j][1] + 3) dp[i][j][2] = dp[i][j][1] + 3;
            if (dp[i][j][2] > dp[i][j][3] + 1) dp[i][j][2] = dp[i][j][3] + 1;

            if (dp[i][j][3] > dp[i][j][0] + 1) dp[i][j][3] = dp[i][j][0] + 1;
            if (dp[i][j][3] > dp[i][j][1] + 2) dp[i][j][3] = dp[i][j][1] + 2;
            if (dp[i][j][3] > dp[i][j][1] + 3) dp[i][j][3] = dp[i][j][2] + 3;
        }                               
    }

    printf("%d\n", dp[0][n - 1][0]);
}
