#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

struct pt {
    int i, j, val;
};

bool cmp(pt a, pt b) {
    return a.val > b.val;
}

const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, 1, 0, -1};

const int N = 1e3;
const int M = 1e3 * 1e3 + 123;

int p[M], rnk[M], sz[M];
bool used[N][N];

int n, m;
ll k;
int a[N][N];
int ans[N][N];
ll need;

void go(int i, int j, int val) {
    if (need == 0) return;
    need--;
    ans[i][j] = val;
    for (int k = 0; k < 4; k++) {
        int newi = i + dx[k];
        int newj = j + dy[k];
        if (0 <= newi && newi < n && 0 <= newj && newj < m) {
            if (used[newi][newj] && ans[newi][newj] != val) {
                go(newi, newj, val);
            }
        }
    }
}

int get(int v) {
    return v == p[v] ? v : p[v] = get(p[v]);
}

void unite(int v, int u) {
    v = get(v);
    u = get(u);
    if (rnk[v] < rnk[u]) swap(v, u);
    p[u] = v;
    sz[v] += sz[u];
    if (rnk[v] == rnk[u]) rnk[v]++;
}

int main() {
#if __APPLE__
    freopen("F.in", "r", stdin);
    freopen("F.out", "w", stdout);
#endif

    scanf("%d%d%I64d", &n, &m, &k);

    vector<pt> q;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &a[i][j]);
            pt cur = {i, j, a[i][j]};
            q.push_back(cur);
            p[i * m + j] = i * m + j;
            sz[i * m + j] = 1;
        }
    }

    sort(q.begin(), q.end(), cmp);
    for (int i = 0; i < (int)q.size(); i++) {
        pt cur = q[i];
        for (int j = 0; j < 4; j++) {
            int newi = cur.i + dx[j];
            int newj = cur.j + dy[j];
            if (0 <= newi && newi < n && 0 <= newj && newj < m) {
                if (used[newi][newj] && get(cur.i * m + cur.j) != get(newi * m + newj)) {
                    unite(cur.i * m + cur.j, newi * m + newj);
                }
            }
        }
        int v = get(cur.i * m + cur.j);
        if (k % cur.val == 0) {
            need = k / cur.val;
            if (sz[v] >= need) {
                puts("YES");
                go(cur.i, cur.j, cur.val);
                for (int j = 0; j < n; j++) {
                    for (int k = 0; k < m; k++) {
                        printf("%d ", ans[j][k]);
                    }
                    puts("");
                }
                return 0;
            }
        }
        used[cur.i][cur.j] = true;
    }
    puts("NO");
}
