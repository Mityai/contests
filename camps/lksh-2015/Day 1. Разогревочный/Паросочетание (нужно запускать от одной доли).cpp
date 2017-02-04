#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int di[] = {-1, 0, 1, 0};
const int dj[] = {0, 1, 0, -1};

vector< vector<int> > g;
vector<char> mark;
vector<int> to;

bool kuhn(int v) {
    if (mark[v] == true) return false;
    mark[v] = true;
    for (int u : g[v]) {
        if (to[u] == -1 || kuhn(to[u])) {
            to[u] = v;
            return true;
        }
    }
    return false;
}

bool correct(int x, int n) {
    return 0 <= x && x < n;
}

int main() {
#if __APPLE__
    freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
#else
    freopen("dominoes.in", "r", stdin);
    freopen("dominoes.out", "w", stdout);
#endif

    int n, m, d1, d2;
    scanf("%d%d%d%d", &n, &m, &d1, &d2);

    int cnt = 0;

    vector<string> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        for (char c : a[i]) {
            if (c == '*') {
                ++cnt;
            }
        }
    }

    if (2 * d2 < d1) {
        printf("%d\n", d2 * cnt);
        return 0;
    }

    g.resize(n * m);
    to.resize(n * m, -1);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (a[i][j] == '*') {
                int cur_pos = i * m + j;
                for (int k = 0; k < 4; k++) {
                    int newi = i + di[k];
                    int newj = j + dj[k];
                    if (correct(newi, n) && correct(newj, m)) {
                        if (a[newi][newj] == '*') {
                            int new_pos = newi * m + newj;
                            g[cur_pos].push_back(new_pos);
                        }
                    }
                }
            }
        }
    }

    int can = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (a[i][j] == '*') {
                mark.assign(n * m, false);
                if (kuhn(i * m + j)) {
                    ++can;
                }
            }
        }
    }
    can >>= 1;

    printf("%d\n", can * d1 + d2 * (cnt - can * 2));
}
