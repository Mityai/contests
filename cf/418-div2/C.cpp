#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

int main() {
#if __APPLE__
    freopen("C.in", "r", stdin);
    freopen("C.out", "w", stdout);
#endif

    int n;
    scanf("%d", &n);

    char s[n + 2];
    scanf(" %s", s);

    int cnt[n][26];
    memset(cnt, 0, sizeof cnt);
    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            for (int j = 0; j < 26; ++j) {
                cnt[i][j] += cnt[i - 1][j];
            }
        }
        ++cnt[i][s[i] - 'a'];
    }

    int cost[26][n];
    memset(cost, 127, sizeof cost);
    for (int c = 0; c < 26; ++c)
    for (int i = 0; i < n; ++i) {
        for (int len = 0; i + len < n; ++len) {
            int j = i + len;
            int here = cnt[j][c];
            if (i > 0) here -= cnt[i - 1][c];
            int need = len + 1 - here;
            cost[c][len] = min(cost[c][len], need);
        }
    }

    int q;
    scanf("%d", &q);

    for (int i = 0; i < q; ++i) {
        int m;
        char c;
        scanf("%d %c", &m, &c);
        int x = c - 'a';
        int lb = 0, rb = n;
        while (lb + 1 < rb) {
            int mb = (lb + rb) / 2;
            if (cost[x][mb] <= m) {
                lb = mb;
            } else {
                rb = mb;
            }
        }
        printf("%d\n", lb + 1);
    }
}
