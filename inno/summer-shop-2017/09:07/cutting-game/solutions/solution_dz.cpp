#include <bits/stdc++.h>
using namespace std;

const int N = 1 << 16;
const int INF = 1e9;

int n;
int a[N];

int main() {
    scanf("%d", &n);

    for (int i = 0; i < n; ++i) {
        scanf("%d", &a[i]);
    }

    int k = __builtin_popcount(n - 1);
    vector<vector<int>> mn(k + 1, vector<int>(n));
    vector<vector<int>> mx(k + 1, vector<int>(n));
    for (int i = 0; i < n; ++i) mn[0][i] = mx[0][i] = a[i];
    for (int i = 1; i <= k; ++i) {
        for (int j = 0; j + (1 << i) <= n; ++j) {
            mn[i][j] = min(mx[i - 1][j], mx[i - 1][j + (1 << (i - 1))]);
            mx[i][j] = max(mn[i - 1][j], mn[i - 1][j + (1 << (i - 1))]);
        }
    }

    if (!(k & 1)) {
        printf("%d\n", mn[k][0]);
    } else {
        printf("%d\n", -mx[k][0]);
    }
}
