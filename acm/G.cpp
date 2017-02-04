#include <bits/stdc++.h>

using namespace std;

const int N = 2345;

vector<int> g[N], g_t[N], gc[N], q, cmp[N];
bool kek[N], gcm[N][N], can[N][N];
vector<bool> used;
int cur = 0, c[N], cnt[N], s, f, tmp;

void dfs1(int v) {
    used[v] = true;
    for (int to : g[v]) {
        if (!used[to]) dfs1(to);
    }
    q.push_back(v);
}

void dfs2(int v) {
    used[v] = true;
    c[v] = cur;
    for (int to : g_t[v]) {
        if (!used[to]) dfs2(to);
    }
}

void go(int v, int x = 0) {
    q.push_back(v);
    used[v] = true;
    if (v == c[f]) {
        tmp = x + cnt[v];
        return;
    }
    for (int to : gc[v]) {
        if (!used[to]) go(to, x + cnt[v]);
    }
}

vector<int> r, w, way;
int v2;

void dfs3(int v) {
    used[v] = true;
    r.push_back(w[v]);
    if (v == v2) {
        way = r;
        return;
    }
    for (int i = 0; i < w.size(); ++i) {
        if (!used[i] && can[w[v]][w[i]]) {
            dfs3(i);
        }
    }
    r.pop_back();
}

vector<int> find(int s, int f) {
    w = cmp[c[s]];
    if (s != f) {
        for (int i = 0; i < w.size(); ++i) {
            if (w[i] == s) {
                swap(w[0], s);
            }
        }
        for (int i = 0; i < w.size(); ++i) {
            if (w[i] == f) {
                w.erase(w.begin() + i);
                break;
            }
        }
        w.push_back(f);
    } else {
        for (int i = 0; i < w.size(); ++i) {
            if (w[i] == s) {
                w.erase(w.begin() + i);
                break;
            }
        }
        w.insert(w.begin(), s);
        w.push_back(s);
    }
    vector<int> res;
    res.reserve(w.size() * w.size() * 3);
    for (int i = 1; i < w.size(); ++i) {
        used.assign(w.size(), false);
        r.clear();
        v2 = i;
        dfs3(i - 1);
        for (int v : way) res.push_back(v);
    }
    return res;
}

vector<int> cmps;

void dfs4(int v) {
    r.push_back(v);
    used[v] = true;
    if (v == v2) {
        cmps = r;
        return;
    }
    for (int to : gc[v]) {
        if (!used[to]) dfs4(to);
    }
    r.pop_back();
}

vector<int> relax(vector<int> a) {
    vector<int> res;
    res.reserve(a.size());
    for (int i = 0; i < a.size(); ++i) {
        if (i == a.size() - 1 || a[i] != a[i + 1])  {
            res.push_back(a[i]);
        }
    }
    return res;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int n, k;
    cin >> n >> k >> s >> f;
    --s;
    --f;
    r.reserve(n);
    used.resize(n);
    q.reserve(n);
    for (int i = 0; i < k; ++i) {
        int x;
        cin >> x;
        --x;
        kek[x] = true;
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            char c;
            cin >> c;
            if (c == '0') continue;
            g[i].push_back(j);
            g_t[j].push_back(i);
            can[i][j] = true;
        }
    }
    for (int i = 0; i < n; ++i) {
        if (!used[i]) dfs1(i);
    }
    reverse(q.begin(), q.end());
    used.assign(n, false);
    for (int v : q) {
        if (!used[v]) {
            dfs2(v);
            ++cur;
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int to : g[i]) {
            if (c[i] != c[to] && !gcm[c[i]][c[to]]) {
                gcm[c[i]][c[to]] = true;
                gc[c[i]].push_back(c[to]);
            }   
        }    
    }
    for (int i = 0; i < n; ++i) {
        cnt[c[i]] += kek[i];
    }
    used.assign(n, false);
    q.clear();
    go(c[s]);
    if (!used[c[f]] || tmp != k) {
        cout << "NO\n";
        return 0;
    }
    cout << "YES\n";
    for (int i = 0; i < n; ++i) {
        cmp[c[i]].push_back(i);
    }
    used.assign(n, false);
    cmps.reserve(n);
    v2 = c[f];
    dfs4(c[s]);
    vector<int> ans;
    if (c[s] == c[f]) {
        ans = find(s, f);
        ans = relax(ans);
        cout << ans.size() << '\n';
        for (int v : ans) cout << v + 1 << " ";
        cout << '\n';
        return 0;
    }
    ans.reserve(n * n);
    int v = s;
    for (int i = 0; i < cmps.size() - 1; ++i) {
        int u = -1, next = -1;
        for (int x : cmp[cmps[i]]) {
            for (int to : g[x]) {
                if (c[to] == cmps[i + 1]) {
                    u = x;
                    next = to;
                    break;
                }
            }
            if (u != -1) break;
        }
        vector<int> qwe = find(v, u);
        //for (int x : qwe) cout << x + 1 << " ";
        //return 0;
        if (qwe.size() == 2 && qwe[0] == qwe[1]) qwe.pop_back();
        for (int x : qwe) {
            ans.push_back(x);
            //cout << x + 1 << " ";
        }
        //cout << endl;
        v = next;        
    }
    vector<int> qwe = find(v, f);
    for (int x : qwe) ans.push_back(x);
    ans = relax(ans);
    cout << ans.size() << '\n';
    for (int x : ans) cout << x + 1 << " ";
    cout << '\n';
}

















