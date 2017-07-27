#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <cstring>

#undef NDEBUG
#include <cassert>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <bitset>
#include <queue>
#include <deque>
#include <complex>
#include <tuple>
#include <unordered_map>
#include <unordered_set>

using namespace std;

#define pb push_back
#define pbk pop_back
#define mp make_pair
#define mt make_tuple
#define fs first
#define sc second
#define sz(s) ((int) (s).size())
#define len(s) ((int) (s).size())
#define all(x) (x).begin(), (x).end()
#define next hunext
#define prev huprev
#define rank hurank
#define hash huhash
#ifdef LOCAL42
#define eprintf(...) fprintf(stderr, __VA_ARGS__)
#else
#define eprintf(...)
#define cerr if (0) cerr
#endif
#if _WIN32 || __WIN32__ || _WIN64 || __WIN64__
#define LLD "%I64d"
#else
#define LLD "%lld"
#endif

typedef long long ll;
typedef long long llong;
typedef long long int64;
typedef unsigned int uint;
typedef unsigned long long ull;
typedef unsigned long long ullong;
typedef unsigned long long lint;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef long double ld;
typedef long double ldouble;

const int inf = 1e9;
const double eps = 1e-9;
const double pi = 4 * atan(1.0);
const int N = int(1e5) + 100;
const int K = 150;
const int LOG = 17;

int a[N], b[N], c[N];

struct magic {
    
    int maxv;
    bool used[N];
    int cnt[N];
    bool rmq[4 * N];
    
    inline void init(int n) {
        for (int i = 0; i <= n; ++i) {
            used[i] = false;
            cnt[i] = 0;
        }
        maxv = 1;
        while (maxv < n + 1) {
            maxv *= 2;
        }
        for (int i = 1; i < 2 * maxv; ++i) {
            rmq[i] = true;
        }
    }
    
    inline void change(int e) {
        if (used[e]) {
            if (--cnt[c[e]] == 0) {
                int pos = c[e] + maxv;
                while (pos > 0 && !rmq[pos]) {
                    rmq[pos] = true;
                    pos >>= 1;
                }
            }
            used[e] = false;
        } else {
            if (cnt[c[e]]++ == 0) {
                int pos = c[e] + maxv;
                rmq[pos] = false;
                while (pos > 1) {
                    pos >>= 1;
                    rmq[pos] = (rmq[(pos << 1)] | (rmq[(pos << 1) | 1]));
                    if (rmq[pos]) {
                        break;
                    }
                }
            }
            used[e] = true;
        }
    }
    
    inline int mex() {
        assert(rmq[1]);
        int v = 1;
        while (v < maxv) {
            if (rmq[(v << 1)]) {
                v <<= 1;
            } else {
                v = (v << 1) | 1;
            }
        }
        return v - maxv;
    }
    
};

struct query {
    
    int x, y, ans;
    
};

int n, cur = 0;
vector<pii> g[N];
int p[LOG][N];
int pe[N], pos[N], h[N], q[N], perm[N];
pii d[N];
query qu[N];
vi need[N];
magic M;

inline int get_rand() {
    return abs((rand() << 15) ^ rand());
}

inline void dfs(int v) {
    pos[v] = cur++;
    for (pii u : g[v]) {
        if (u.fs != p[0][v]) {
            h[u.fs] = h[v] + 1;
            pe[u.fs] = u.sc;
            p[0][u.fs] = v;
            dfs(u.fs);
        }
    }
}

struct cmp {
    
    int v;
    
    cmp(int v) : v(v) {}
    
    inline int ind(int u) {
        if (pos[u] >= pos[v]) {
            return pos[u];
        } else {
            return n + pos[u];
        }
    }
    
    inline bool operator ()(int x, int y) {
        return ind(qu[x].y) < ind(qu[y].y);
    }
    
};

inline int get_lca(int x, int y) {
    if (h[x] < h[y]) {
        swap(x, y);
    }
    for (int i = LOG - 1; i >= 0; --i) {
        if (p[i][x] != -1 && h[p[i][x]] >= h[y]) {
            x = p[i][x];
        }
    }
    if (x == y) {
        return x;
    }
    for (int i = LOG - 1; i >= 0; --i) {
        if (p[i][x] != p[i][y]) {
            x = p[i][x];
            y = p[i][y];
        }
    }
    return p[0][x];
}

inline void go2(int v, int pv) {
    while (v != pv) {
        M.change(pe[v]);
        v = p[0][v];
    }
}

inline void go(int x, int y) {
    int xy = get_lca(x, y);
    go2(x, xy);
    go2(y, xy);
}

inline void solve(int v) {
    sort(all(need[v]), cmp(v));
    M.init(n);
    int x = v, y = v;
    for (int num : need[v]) {
        go(x, qu[num].x);
        x = qu[num].x;
        go(y, qu[num].y);
        y = qu[num].y;
        qu[num].ans = M.mex();
    }
}

int main() {
#ifdef LOCAL42
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int m;
    cin >> n >> m;
    for (int i = 0; i < n - 1; ++i) {
        scanf("%d %d %d", a + i, b + i, c + i);
        --a[i];
        --b[i];
        c[i] = min(c[i], n);
        g[a[i]].pb(mp(b[i], i));
        g[b[i]].pb(mp(a[i], i));
    }
    for (int i = 0; i < m; ++i) {
        scanf("%d %d", &qu[i].x, &qu[i].y);
        --qu[i].x;
        --qu[i].y;
    }
    p[0][0] = -1;
    dfs(0);
    for (int i = 1; i < LOG; ++i) {
        for (int j = 0; j < n; ++j) {
            if (p[i - 1][j] == -1) {
                p[i][j] = -1;
            } else {
                p[i][j] = p[i - 1][p[i - 1][j]];
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        perm[i] = i;
        d[i] = mp(inf, -1);
    }
    for (int i = 0; i < n; ++i) {
        int j = i + get_rand() % (n - i);
        swap(perm[i], perm[j]);
    }
    int l = 0, r = 0;
    for (int i = 0; i < min(n, K); ++i) {
        d[perm[i]] = mp(0, perm[i]);
        q[r++] = perm[i];
    }
    while (l < r) {
        int v = q[l++];
        pii cur(d[v].fs + 1, d[v].sc);
        for (pii u : g[v]) {
            if (d[u.fs].fs > cur.fs) {
                d[u.fs] = cur;
                q[r++] = u.fs;
            }
        }
    }
    for (int i = 0; i < m; ++i) {
        need[d[qu[i].x].sc].pb(i);
    }
    for (int i = 0; i < n; ++i) {
        if (sz(need[i]) > 0) {
            solve(i);
        }
    }
    for (int i = 0; i < m; ++i) {
        printf("%d\n", qu[i].ans);
    }
    return 0;
}