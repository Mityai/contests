#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <cmath>

typedef long long ll;

using namespace std;

const int MAXN = 101, MAXM = 10001;

int d[MAXN][MAXM], m[MAXN], c[MAXN];

int main() {
    freopen("backpack.in", "r", stdin);
    freopen("backpack.out", "w", stdout);

    int N, M;
    scanf("%d%d", &N, &M);

    for (int i = 1; i <= N; i++) {
        scanf("%d", &m[i]);
    }

    for (int i = 1; i <= N; i++) {
        scanf("%d", &c[i]);
    }

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            d[i][j] = d[i - 1][j];

            if (j >= m[i]) {
                if (d[i][j] < d[i - 1][j - m[i]] + c[i]) {
                    d[i][j] = d[i - 1][j - m[i]] + c[i];
                }
            }
        }
    }

    printf("%d\n", d[N][M]);

    vector<int> ans;

    for (int i = N, j = M; d[i][j] != 0;) {
        if (d[i][j] != d[i - 1][j]) {
            ans.push_back(i);

            j -= m[i];
            --i;
        } else {
            --i;
        }
    }

    printf("%d\n", (int)ans.size());

    for (int i = 0; i < ans.size(); i++) {
        printf("%d ", ans[i] - 1);
    }
}