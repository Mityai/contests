#include <bits/stdc++.h>
using namespace std;

int main() {
#if __APPLE__
    // freopen("02.in", "r", stdin);
    // freopen("02.out", "w", stdout);
#endif

    int h, w, x, y;
    scanf("%d%d%d%d", &h, &w, &x, &y);

    vector<vector<int>> b(h + x, vector<int>(w + y));
    for (int i = 0; i < h + x; ++i) {
        for (int j = 0; j < w + y; ++j) {
            scanf("%d", &b[i][j]);
        }
    }

    vector<vector<int>> a(h, vector<int>(w));
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            if (i < x || j < y) {
                printf("%d ", b[i][j]);
            } else {
                printf("%d ", b[i][j] - a[i - x][j - y]);
            }
        }
        putchar('\n');
    }
}
