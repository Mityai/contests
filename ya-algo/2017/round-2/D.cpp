#include <bits/stdc++.h>
using namespace std;

const int N = 2000;

const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, 1, 0, -1};

int a[N][N];
int cnt = 0;

void go(int x, int y) {
    a[x][y] = (a[x][y] + 1) % 5;
    if (a[x][y] == 1) ++cnt;
    if (a[x][y] == 0) {
        --cnt;
        for (int k = 0; k < 4; ++k) {
            go(x + dx[k], y + dy[k]);
        }
    }
}

int main() {
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; ++i) {
        int x, y;
        scanf("%d%d", &x, &y);

        x += N / 2;
        y += N / 2;

        go(x, y);
        printf("%d\n", cnt);
    }
}
