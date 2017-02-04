#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

const int N = 3000;

int n, m;
int fenw[N][N];
vector<int> a, b;

void setval(int x, int y, int val) {
    for (int i = x; i < n; i = (i | (i + 1))) {
        for (int j = y; j < m; j = (j | (j + 1))) {
            fenw[i][j] = max(fenw[i][j], val);
        }
    }
}

int getmax(int x, int y) {
    int ret = 0;
    for (int i = x; i >= 0; i = (i & (i + 1)) - 1) {
        for (int j = y; j >= 0; j = (j & (j + 1)) - 1) {
            ret = max(ret, fenw[i][j]);
        }
    }
    return ret;
}

bool cmp(int A, int B) {
    A >>= 13;
    B >>= 13;
    return a[A] < a[B];
}

int main() {
    freopen("lcis.in", "r", stdin);
    freopen("lcis.out", "w", stdout);

    scanf("%d%d", &n, &m);
    a.resize(n);
    b.resize(m);

    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    for (int i = 0; i < m; i++) {
        scanf("%d", &b[i]);
    }

    for (int i = n - 1; i >= 0; i--) {
        bool ok = true;
        for (int j = 0; j < m; j++) {
            if (a[i] == b[j]) {
                ok = false;
                break;
            }
        }
        if (ok) {
            a.erase(a.begin() + i);
        }
    }
    n = a.size();

    for (int i = m - 1; i >= 0; i--) {
        bool ok = true;
        for (int j = 0; j < n; j++) {
            if (b[i] == a[j]) {
                ok = false;
                break;
            }
        }
        if (ok) {
            b.erase(b.begin() + i);
        }
    }
    m = b.size();

    vector<int> p;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (a[i] == b[j]) {
                p.push_back((i << 13) + j);
            }
        }
    }

    sort(p.begin(), p.end(), cmp);

    vector< pair< int, pair<int, int> > > todo;
    for (int i = 0; i < (int)p.size(); i++) {
        if (i > 0 && a[p[i - 1] >> 13] != a[p[i] >> 13]) {
            for (auto v : todo) {
                setval(v.se.fi, v.se.se, v.fi);
            }
            todo.clear();
        }
        int x = getmax(p[i] >> 13, p[i] % (1 << 13)) + 1;
        todo.push_back({x, {p[i] >> 13, p[i] % (1 << 13)}});
    }
    for (auto v : todo) {
        setval(v.se.fi, v.se.se, v.fi);
    }

    printf("%d\n", getmax(n - 1, m - 1));
}
