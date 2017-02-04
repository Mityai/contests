#include <bits/stdc++.h>
using namespace std;

const int N = 5e3;
const int C = 26;

int dp[N + 1][N + 1][C];

int main() {
    int n;
    scanf("%d", &n);

    char s[N + 3];
    scanf("%s", s + 1);

    for (int c = 0; c < C; ++c) dp[0][0][c] = 1;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
        }
    }
}
