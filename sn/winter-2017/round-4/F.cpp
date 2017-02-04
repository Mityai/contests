#include <bits/stdc++.h>
using namespace std;

const int N = 51;

int n, m;
char c[N][N];
int cnt[N][N];

void goRed(int i, int j) {
    ++cnt[i][j];
    if (i + 1 < n && j + 1 < m) {
        if (c[i + 1][j + 1] == 'R' || c[i + 1][j + 1] == 'M') {
            goRed(i + 1, j + 1);
        }
    }
}

void goBlue(int i, int j) {
    ++cnt[i][j];
    if (i + 1 < n && j - 1 >= 0) {
        if (c[i + 1][j - 1] == 'B' || c[i + 1][j - 1] == 'M') {
            goBlue(i + 1, j - 1);
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++i) {
        scanf(" %s", c[i]);
    }

    int ans = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (c[i][j] != '.') {
                if (cnt[i][j] == 0 && c[i][j] != 'B') {
                    goRed(i, j);
                    ++ans;
                }
            }
        }
    }

    memset(cnt, 0, sizeof cnt);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (c[i][j] != '.') {
                if (cnt[i][j] == 0 && c[i][j] != 'R') {
                    goBlue(i, j);
                    ++ans;
                }
            }
        }
    }

    cout << ans << endl;
}
