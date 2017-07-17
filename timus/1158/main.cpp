#include <bits/stdc++.h>
using namespace std;

const int LEN = 10;
const int P = 10;
const int N = LEN * P + 7;
const int M = 50;

int n, m, p;

int nxt[N][M], par[N], sufflink[N], col[N], go[N][M];
bool leaf[N];
map<char, int> to;

int tc = 1;
int ROOT = 1;

void add(const string& s) {
    int v = ROOT;
    for (char c : s) {
        int x = to[c];
        if (!nxt[v][x]) nxt[v][x] = ++tc, par[tc] = v, col[tc] = x;
        v = nxt[v][x];
    }
    leaf[v] = true;
}

int getLink(int v, int c);

int getSuffLink(int v) {
    if (!sufflink[v]) {
        if (v == ROOT || par[v] == ROOT) {
            sufflink[v] = ROOT;
        } else {
            sufflink[v] = getLink(getSuffLink(par[v]), col[v]);
        }
    }
    return sufflink[v];
}

int getLink(int v, int c) {
    if (!go[v][c]) {
        if (nxt[v][c]) {
            go[v][c] = nxt[v][c];
        } else if (v == ROOT) {
            go[v][c] = ROOT;
        } else {
            go[v][c] = getLink(getSuffLink(v), c);
        }
    }
    return go[v][c];
}

typedef long long ll;
const ll BASE = 1e9;

struct BigInt {
    vector<ll> d;

    BigInt(ll x = 0) : d({x}) {}

    BigInt& operator += (const BigInt& oth) {
        for (int i = 0, carry = 0; i < max(d.size(), oth.d.size()) || carry; ++i) {
            if (i == d.size()) d.push_back(0);
            d[i] += (i < oth.d.size() ? oth.d[i] : 0) + carry;
            carry = (d[i] >= BASE);
            if (carry) d[i] -= BASE;
        }
        while (d.size() >= 2 && d.back() == 0) d.pop_back();
        return *this;
    }

    void print() {
        printf("%lld", d.back());
        for (int i = int(d.size()) - 2; i >= 0; --i) {
            printf("%09lld", d[i]);
        }
        puts("");
    }
};

BigInt bfs() {
    queue<int> q({ROOT});
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int i = 0; i < n; ++i) {
            int u = nxt[v][i];
            if (u == 0) continue;
            if (leaf[v] || leaf[getSuffLink(u)]) leaf[u] = true;
            q.push(u);
        }
    }

    vector<vector<BigInt>> dp(2, vector<BigInt>(tc + 1));
    dp[0][ROOT] = 1;
    for (int l = 0; l < m; ++l) {
        int p = (l & 1);
        int q = 1 - p;
        for (int i = 1; i <= tc; ++i) {
            dp[q][i].d = {0};
        }
        for (int v = 1; v <= tc; ++v) {
            if (leaf[v]) continue;
            for (int c = 0; c < n; ++c) {
                int u = getLink(v, c);
                if (leaf[u]) continue;
                dp[q][u] += dp[p][v];
            }
        }
    }

    BigInt ans;
    for (int i = 1; i <= tc; ++i) {
        ans += dp[m & 1][i];
    }
    return ans;
}

int main() {
#if __APPLE__
    //freopen("in", "r", stdin);
#endif

    cin >> n >> m >> p;

    string ALPHA;
    getline(cin, ALPHA);
    getline(cin, ALPHA);
    for (int i = 0; i < n; ++i) {
        to[ALPHA[i]] = i;
    }

    string s;
    for (int i = 0; i < p; ++i) {
        getline(cin, s);
        add(s);
    }

    BigInt ans = bfs();
    ans.print();
}
