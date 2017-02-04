#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <climits>
#include <string>

typedef long long ll;

using namespace std;

const int INF = INT_MAX;

int main() {
    freopen("bars.in", "r", stdin);
    freopen("bars.out", "w", stdout);

    int L, n;
    scanf("%d%d", &L, &n);

    n += 2;
    int c[n];
    c[0] = 0;
    for (int i = 1; i < n - 1; i++) {
        scanf("%d", &c[i]);
    }
    c[n - 1] = L;

    vector<vector<int> > d(n, vector<int> (n, 0));
    for (int k = 2; k < n; k++) {
        for (int i = 0; i < n - k; i++) {
            int j = i + k;
            if (k == 2) {
                d[i][j] = c[j] - c[i];
            } else {
                d[i][j] = INF;
                for (int t = i + 1; t < j; t++) {
                    d[i][j] = min(d[i][j], d[i][t] + d[t][j] + c[j] - c[i]);
                }
            }
        }
    }

    printf("%d\n", d[0][n - 1]);
}