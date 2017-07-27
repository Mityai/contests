#include <bits/stdc++.h>
using namespace std;
 
 
template<typename T1, typename T2>
ostream &operator<<(ostream &out, pair<T1, T2> &p) {
    out << "{" << p.first << ", " << p.second << "} ";//optional
    return out;
}
 
template<typename T1, typename T2>
istream &operator>>(istream &in, pair<T1, T2> &p) {
    in >> p.first >> p.second;
    return in;
}
 
template<typename T>
istream &operator>>(istream &in, vector<T> &arr) {
    for (auto &i : arr)
        in >> i;
    return in;
}
 
template<typename T>
ostream &operator<<(ostream &out, vector<T> &arr) {
    for (auto i : arr)
        out << i << " ";//optional
    out << endl;
    return out;
}
 
 
/*
 *
 ifstream fin("mail.in");
 ofstream fout("mail.out");
 
 
ifstream fin("/Users/Christian/CLionProjects/complex/input.txt");
ofstream fout("/Users/Christian/CLionProjects/complex/output.txt");
 */
 
ifstream fin("mail.in");
ofstream fout("mail.out");
 
class SegTree {
public:
    vector<int> tr;
    int m, id, parent;
 
    SegTree() {
        m = 0, id = 1e9, parent = -1;
    }
 
    SegTree(int n, int _id) {
        id = _id;
        m = 1;
        while (m < n) {
            m <<= 1;
        }
        tr.resize(m << 1);
        //cerr << id << ' ' << tr.size() << endl;
    }
 
    int get_max(int l, int r) {
        l += m, r +=m;
        int ret = 0;
        while (l <= r) {
            if (l & 1) {
                ret = max(ret, tr[l]);
            }
            if (!(r & 1)) {
                ret = max(ret, tr[r]);
            }
            l = (l + 1) >> 1;
            r = (r - 1) >> 1;
        }
        return ret;
    }
 
    void change(int ind, int val)  {
        ind += m;
        tr[ind] = val;
        while (ind > 1) {
            ind >>= 1;
            tr[ind] = max(tr[ind << 1], tr[(ind<<1) + 1]);
        }
    }
};
vector<SegTree*> trees;
vector<int> h;
vector<bool> used;
vector<int> c;
vector<int> heavy;
vector<int> p;
vector<vector<int>> up;
vector<vector<int>> g;
vector<int> pos;
vector<int> a;
 
void dfs(int v, int depth, int pr) {
    p[v] = pr;
    up[0][v] = pr;
    h[v] = depth;
    used[v] = 1;
    c[v] = 1;
 
    int max = -1;
    int max_ind = -1;
    for (auto u : g[v]) {
        if (!used[u]) {
            dfs(u, depth + 1, v);
            c[v] += c[u];
            if (max < c[u]) {
                max = c[u];
                max_ind = u;
            }
        }
    }
    if (max_ind >= 0) {
        heavy[v] = max_ind;
    }
}
int id = 0;
void make_segtr(int v, int sz) {
    used[v] = true;
    bool flag = false;
    if (heavy[v] >= 0) {
        flag = true;
        make_segtr(heavy[v], sz + 1);
        trees[v] = trees[heavy[v]];
    }
    else {
        trees[v] = new SegTree(sz + 1, id++);
    }
    pos[v] = sz;
    trees[v]->change(pos[v], a[v]);
 
    if (sz == 0) {
        trees[v]->parent = p[v];
    }
    for (auto u : g[v]) {
        if (!used[u]) {
            make_segtr(u, 0);
        }
    }
}
 
int parent(int x,int j){for (int i=0; i<20; i++) if (j&(1<<i)) x = up[i][x]; return x;}
int lca(int a, int b) {
    if (h[a]<h[b]) swap(a,b);
    a=parent(a,h[a]-h[b]);
    for (int i(20 - 1); i >= 0; i--)
        if (up[i][a] != up[i][b])
            a = up[i][a], b = up[i][b];
    return a == b? a : up[0][a];
}
 
 
signed main()
{
    int n;
    fin >> n;
    a.resize(n);
    h.resize(n);
    pos.resize(n);
    g.resize(n);
    used.resize(n, false);
    c.resize(n);
    heavy.resize(n, -1);
    p.resize(n);
    trees.resize(n);
    up.resize(20, vector<int>(n, 0));
 
    for (int i = 0; i < n; ++i) {
        fin >> a[i];
    }
    int cnt = 0;
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cnt++;
        fin >> a >> b;
        a--, b--;
        if (a < 0 || b < 0) {
            cout << "LOOOOOL";
        }
        g[a].push_back(b);
        g[b].push_back(a);
    }
    dfs(0, 0, 0);
    for (int i = 0; i < n; ++i) {
        up[0][i] = p[i];
    }
    for (int i = 0; i + 1 < up.size(); ++i) {
        for (int j = 0; j < n; ++j) {
            up[i + 1][j] = up[i][up[i][j]];
        }
    }
    fill(used.begin(), used.end(), false);
    make_segtr(0, 0);
    int qu;
    fin >> qu;
    for (int i = 0; i < qu; ++i) {
        char cmd;
        fin >> cmd;
        int start;
        fin >> start;
        start--;
        if (cmd == '!' ) {
            fin >> a[start];
            trees[start]->change(pos[start], a[start]);
        } else {
            int to;
            fin >> to;
            to--;
            int a = lca(start, to);
            int ans = 0;
            while (trees[start]->id != trees[a]->id) {
 
                ans = max(ans, trees[start]->get_max(0, pos[start]));
                start = trees[start]->parent;
            }
            ans = max(ans, trees[start]->get_max(pos[a], pos[start]));
            while (trees[to]->id != trees[a]->id) {
 
                ans = max(ans, trees[to]->get_max(0, pos[to]));
                to = trees[to]->parent;
            }
            ans = max(ans, trees[to]->get_max(pos[a], pos[to]));
            fout << ans << endl;
        }
    }
    return 0;
}
