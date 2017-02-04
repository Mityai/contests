#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

const int N = 1e5;

int fenw[N];

void add(int pos, int val) {
    for (int i = pos; i < N; i = (i | (i + 1))) {
        fenw[i] += val;
    }
}

int sum(int pos) {
    int ret = 0;
    for (int i = pos; i >= 0; i = (i & (i + 1)) - 1) {
        ret += fenw[i];
    }
    return ret;
}

int main() {
    freopen("mutation.dat", "r", stdin);
    freopen("mutation.sol", "w", stdout);

    int n;
    scanf("%d", &n);

    int a[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        --a[i];
    }

    int to[n];
    memset(to, -1, sizeof to);
    {
        int cnt = 0;
        for (int i = 0; i < n; i++) {
            if (to[a[i]] == -1) to[a[i]] = cnt++;
            a[i] = to[a[i]];
        }
    }

    int fir[n], lst[n];
    memset(fir, -1, sizeof fir);
    memset(lst, -1, sizeof lst);
    vector< vector<int> > pos(n);
    for (int i = 0; i < n; i++) {
        if (fir[a[i]] == -1) fir[a[i]] = i;
        lst[a[i]] = i;
        pos[a[i]].push_back(i);
    }

    vector< pair< pair<int, int>, int > > q;
    for (int i = 0; i < n; i++) {
        q.push_back({{lst[i], fir[i]}, i});
    }

    sort(q.begin(), q.end());

    int cnt[n];
    memset(cnt, 0, sizeof cnt);

    int nxt[n];
    memset(nxt, -1, sizeof nxt);
    for (int i = 0, j = 0; i < n; i++) {
        if (nxt[a[i]] != -1) {
            add(nxt[a[i]], -1);
        }
        nxt[a[i]] = i;
        add(nxt[a[i]], 1);
        while (j < (int)q.size() && q[j].fi.fi < i) j++;
        while (j < (int)q.size() && q[j].fi.fi == i) {
            int l = q[j].fi.se;
            int r = q[j].fi.fi;
            int k = q[j].se;
            cnt[k] = sum(r) - sum(l - 1) - 1;
            j++;
        }
    }

    int perm[n];
    for (int i = 0; i < n; i++) perm[i] = i;

    sort(perm, perm + n, [&](int a, int b) {return cnt[a] > cnt[b];});

    bool moved[n];
    memset(moved, 0, sizeof moved);

    memset(fenw, 0, sizeof fenw);
    for (int i = 0; i < n; i++) {
        int k = perm[i];

        int d = lst[k] - fir[k] + 1 - (sum(lst[k]) - sum(fir[k]));
        if (d != pos[k].size() && !pos[k].empty()) {
            moved[k] = true;
            for (int j : pos[k]) {
                add(j, 1);
            }
        }
    }

    int ans = 0;
    for (int i = 0; i < n; i++) {
        ans += moved[i];
    }

    printf("%d\n", ans);
}
