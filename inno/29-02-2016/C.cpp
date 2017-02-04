#include <bits/stdc++.h>
using namespace std;

const int N = 8;
const int dx[] = {0, 1, 0, -1};
const int dy[] = {-1, 0, 1, 0};

bool used[N + 4][N + 4];

int main() {
    freopen("c.in", "r", stdin);
    freopen("c.out", "w", stdout);

    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        used[a + 1][b + 1] = true;
    }

    int ans = 0;
    for (int i = 1; i <= N + 2; i++) {
        for (int j = 1; j <= N + 2; j++) {
            if (!used[i][j]) {
                for (int k = 0; k < 4; k++) {
                    ans += used[i + dx[k]][j + dy[k]];
                }
            }
        }
    }

    printf("%d\n", ans);
}
