#define filesfl 0
#define consolefl 01
#define fname "keke"
// evgenstf - batya

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <cassert>
#include <stdint.h>
#include <utility>
#include <random>

#include <cmath>
#include <algorithm>

#include <set>
#include <vector>
#include <map>
#include <string>
#include <queue>
#include <stack>
#include <bitset>
#include <unordered_set>
#include <unordered_map>

#define forn(i, n) for (ll i = 0; i < n; ++i)
#define fornn(i, q, n) for (ll i = q; i < n; ++i)
#define rforn(i, n) for (ll i = n; i >= 0; i--)
#define rfornn(i, m, n) for (ll i = m; i >= n; i--)

#define inb push_back
#define outb pop_back
#define X first
#define Y second
#define Z third
#define mk make_pair
#define _i "%d"
#define _ll "%I64d"
#define pii pair<ll, ll>
#define times clock() * 1.0 / CLOCKS_PER_SEC
#define all(v) v.begin(), v.end()

#define nsc(n) scanf("%d", &n)
#define nmsc(n, m) scanf("%d%d", &n, &m)

typedef long double ld;
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int uint;

using namespace std;

vector<vector<int>> gt;

ll got(int v, int k, int p = -1, int d = 0) {
    int ret = (d + k - 1) / k;
    for (int u : gt[v]) {
        if (p != u) {
            ret += got(u, k, v, d + 1);
        }
    }
    return ret;
}

ll stupid(int n, int k, vector<pair<int, int>>& edges) {
    gt.clear();
    gt.resize(n);
    for (int i = 0; i < n - 1; ++i) {
        int a = edges[i].first;
        int b = edges[i].second;
        gt[a].push_back(b);
        gt[b].push_back(a);
    }

    ll ans = 0;
    for (int i = 0; i < n; ++i) {
        ans += got(i, k);
    }

    return ans / 2;
}

mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

void gen(int& n, int& k, vector<pair<int, int>>& edges) {
    const int N = 2000;
    n = rng() % N;
    k = rng() % 5 + 1;
    edges.clear();
    for (int i = 1; i < n; ++i) {
        int a = rng() % i;
        int b = i;
        edges.push_back(make_pair(a, b));
    }
}

int n, k;
ll ans = 0;
vector<vector<ll> > dp;
vector<vector<int> > ways;

void go(int v, int parent) {
    vector<ll> now(k + 5);
    now[0] = 1;

    forn(ii, ways[v].size()) {
        int u = ways[v][ii];
        if (u == parent)
            continue;

        go(u, v);
        forn(i, k) 
            forn(j, k) {
                ans += dp[u][i] * now[j] * (((k - (i + j + 1) % k) + k) % k);
            }
        forn(i, k) {
            now[(i + 1) % k] += dp[u][i];
        }
    }
    dp[v] = now;
    if (parent != -1) {
        ll q = 0;
        forn(j, k)
            q += dp[v][j];
        ans += q * (n - q);
    }
}

ll solve(int n, int k, vector<pair<int, int>>& edges) {
    ways.clear();
    dp.clear();
    ways.resize(n);
    dp.resize(n);
    ans = 0;
    forn(i, n - 1) {
        int a = edges[i].first;
        int b = edges[i].second;
        ways[a].inb(b);
        ways[b].inb(a);
    }

    go(0, -1);

    return ans / k;
}

int main() {
    ios_base::sync_with_stdio(0);
#ifdef _DEBUG
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#else
    if (filesfl) {
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    } else {
        if (!consolefl) {
            freopen(fname".in", "r", stdin);
            freopen(fname".out", "w", stdout);
        }
    }
#endif

    while (true) {
        vector<pair<int, int>> edges;
        gen(n, k, edges);
        if (solve(n, k, edges) != stupid(n, k, edges)) {
            cout << solve(n, k, edges) << ' ' << stupid(n, k, edges) << endl;
            cout << "FAIL" << endl;
            return 0;
        } else cout << "OK" << endl;
    }
}
