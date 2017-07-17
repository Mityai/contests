#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

void yes() {
    puts("YES");
    exit(0);
}

int main() {
#if __APPLE__
    //freopen("B.in", "r", stdin);
    //freopen("B.out", "w", stdout);
#endif

    ios_base::sync_with_stdio(false);

    int n, m;
    cin >> n >> m;

    vector<string> a(n);
    int si, sj;
    int fi, fj;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        for (int j = 0; j < m; ++j) {
            if (a[i][j] == 'S') {
                si = i;
                sj = j;
                a[i][j] = '1';
            }
            if (a[i][j] == 'T') {
                fi = i;
                fj = j;
                a[i][j] = '2';
            }
        }
    }

    for (int dx = si + 1; dx < n && a[dx][sj] == '.'; ++dx) {
        a[dx][sj] = '1';
    }
    for (int dx = si - 1; dx >= 0 && a[dx][sj] == '.'; --dx) {
        a[dx][sj] = '1';
    }
    for (int dy = sj + 1; dy < m && a[si][dy] == '.'; ++dy) {
        a[si][dy] = '1';
    }
    for (int dy = sj - 1; dy >= 0 && a[si][dy] == '.'; --dy) {
        a[si][dy] = '1';
    }

    for (int dx = fi + 1; dx < n && a[dx][fj] == '.'; ++dx) {
        a[dx][fj] = '2';
    }
    for (int dx = fi - 1; dx >= 0 && a[dx][fj] == '.'; --dx) {
        a[dx][fj] = '2';
    }
    for (int dy = fj + 1; dy < m && a[fi][dy] == '.'; ++dy) {
        a[fi][dy] = '2';
    }
    for (int dy = fj - 1; dy >= 0 && a[fi][dy] == '.'; --dy) {
        a[fi][dy] = '2';
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (a[i][j] == '1') {
                for (int di = i - 1; di >= 0; --di) {
                    if (a[di][j] == '*' || a[di][j] == '1') break;
                    if (a[di][j] == '2') {
                        yes();
                    }
                }
                for (int di = i + 1; di < n; ++di) {
                    if (a[di][j] == '*' || a[di][j] == '1') break;
                    if (a[di][j] == '2') {
                        yes();
                    }
                }
                for (int dj = j - 1; dj >= 0; --dj) {
                    if (a[i][dj] == '*' || a[i][dj] == '1') break;
                    if (a[i][dj] == '2') {
                        yes();
                    }
                }
                for (int dj = j + 1; dj < m; ++dj) {
                    if (a[i][dj] == '*' || a[i][dj] == '1') break;
                    if (a[i][dj] == '2') {
                        yes();
                    }
                }
            }
        }
    }

    puts("NO");
}
