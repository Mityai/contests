#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>

typedef long long ll;

using namespace std;

const int MAX_NM = 5000;

int d[MAX_NM][MAX_NM];

int main() {
    freopen("interview.in", "r", stdin);
    freopen("interview.out", "w", stdout);

    int n, m;
    scanf("%d%d", &n, &m);

    int a[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    int b[m];
    for (int i = 0; i < m; i++) {
        scanf("%d", &b[i]);
    }

    int ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (a[i] == b[j]) {
                d[i][j] = 1;
                for (int k = 0; k < i; k++) {
                    if (a[k] < a[i] && d[i][j] < d[k][j] + 1) {
                        d[i][j] = d[k][j] + 1;
                    }
                }
            } else if (j > 0) {
                d[i][j] = d[i][j - 1];
            }
            ans = max(ans, d[i][j]);
        }
    }

    printf("%d\n", ans);
}