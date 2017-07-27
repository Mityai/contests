#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct BigInt {
    static const int base = 1e9;
    vector<int> d;

    BigInt(int x = 0) : d({x}) {
    }

    BigInt& operator += (const BigInt& oth) {
        for (int i = 0, carry = 0; i < max(d.size(), oth.d.size()) || carry; ++i) {
            if (i == d.size()) d.push_back(0);
            d[i] += carry + (i < oth.d.size() ? oth.d[i] : 0);
            carry = d[i] >= base;
            if (carry) d[i] -= base;
        }
        while (d.size() >= 2 && d.back() == 0) d.pop_back();
        return *this;
    }

    void print() {
        printf("%d", d.back());
        for (int i = int(d.size()) - 2; i >= 0; --i) {
            printf("%09d", d[i]);
        }
        puts("");
    }
};

int main() {
    freopen("dfa.in", "r", stdin);
    freopen("dfa.out", "w", stdout);

    char str[28];
    scanf("%s", str);

    int alpha = strlen(str);
    int k, s, l;
    scanf("%d%d%d", &k, &s, &l);
    --s;

    vector<char> term(k);
    for (int i = 0; i < l; ++i) {
        int x;
        scanf("%d", &x);
        term[x - 1] = true;
    }

    vector<vector<int>> g(k, vector<int>(alpha));
    for (int i = 0; i < k; ++i) {
        for (int j = 0; j < alpha; ++j) {
            scanf("%d", &g[i][j]);
            --g[i][j];
        }
    }
    vector<vector<char>> f(k, vector<char>(alpha));
    for (int i = 0; i < k; ++i) {
        for (int j = 0; j < alpha; ++j) {
            int x;
            scanf("%d", &x);
            f[i][j] = (x == 1);
        }
    }

    int n;
    scanf("%d", &n);

    for (int j = 0; j < alpha; ++j) {
        vector<char> used(k, 0);
        for (int i = 0; i < k; ++i) {
            int v = i;
            if (used[v] == 0 && f[v][j]) {
                vector<int> path;
                while (true) {
                    used[v] = 1;
                    path.push_back(v);
                    int u = g[v][j];
                    if (f[v][j] == 0) {
                        for (int w : path) {
                            g[w][j] = u;
                            used[w] = 2;
                        }
                        break;
                    } else if (used[u] == 2) {
                        for (int w : path) {
                            g[w][j] = g[u][j];
                            used[w] = 2;
                        }
                        break;
                    } else if (used[u] == 1) {
                        for (int w : path) {
                            g[w][j] = -1;
                            used[w] = 2;
                        }
                        break;
                    } else {
                        v = u;
                    }
                }
            }
        }
    }

    vector<vector<BigInt>> dp(n + 1, vector<BigInt>(k));
    dp[0][s] = 1;
    for (int len = 0; len < n; ++len) {
        for (int v = 0; v < k; ++v) {
            for (int c = 0; c < alpha; ++c) {
                if (g[v][c] != -1) {
                    dp[len + 1][g[v][c]] += dp[len][v];
                }
            }
        }
    }

    BigInt ans = 0;
    for (int i = 0; i < k; ++i) {
        if (term[i]) {
            ans += dp[n][i];
        }
    }
    ans.print();
}
