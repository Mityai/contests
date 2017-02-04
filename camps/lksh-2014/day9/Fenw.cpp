#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
#include <cmath>
#include <set>
#include <climits>

typedef long long ll;

using namespace std;

const int MAXN = 1000;

int fenw[MAXN + 1][MAXN + 1];

int x, y;

int up(int i) {
    return (i | (i + 1));
}

int down(int i) {
    return (i & (i + 1));
}

int sum(int ii, int jj) {
    int res = 0;

    for (int i = ii; i >= 0; i = down(i) - 1) {
        for (int j = jj; j >= 0; j = down(j) - 1) {
            res += fenw[i][j];
        }
    }

    return res;
}

void add(int ii, int jj, int k) {
    for (int i = ii; i <= x; i = up(i)) {
        for (int j = jj; j <= y; j = up(j)) {
            fenw[i][j] += k;
        }
    }
}

int main() {
    freopen("camomiles.in", "r", stdin);
    freopen("camomiles.out", "w", stdout);

    scanf("%d%d", &x, &y);

    int n;
    scanf("%d", &n);

    while (n--) {
        int t;
        scanf("%d", &t);

        if (t == 1) {
            int i, j, k;
            scanf("%d%d%d", &i, &j, &k);

            add(i, j, k);
        }

        if (t == 2) {
            int i1, j1, i2, j2;
            scanf("%d%d%d%d", &i1, &j1, &i2, &j2);

            --i1;
            --j1;

            printf("%d\n", sum(i2, j2) - sum(i1, j2) - sum(i2, j1) + sum(i1, j1));
        }
    }
}
