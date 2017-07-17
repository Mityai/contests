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

const int inf = 1e9 + 5;
const ll linf = 1e18 + 5;
const ld eps = 1e-9;

const ll dd = 2e5 + 7;
const ll maxn = 2e3 + 10;

const ll mod = 1e9 + 7;

using namespace std;

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

    const int N = 50;
    vector<string> names(N);

    for (int i = 0; i < N; ++i) {
        names[i] = char('A' + (i >= 26));
        names[i] += char('a' + i % 26);
    }

    int n, k;
    cin >> n >> k;

    int m = n - k + 1;

    vector<string> a(m);
    for (int i = 0; i < m; ++i) {
        cin >> a[i];
    }

    vector<string> ans(n);
    for (int i = 0; i < k - 1; ++i) {
        ans[i] = names[i];
    }
    for (int i = k - 1; i < n; ++i) {
        if (a[i - (k - 1)] == "YES") {
            for (int j = 0; j < N; ++j) {
                bool ok = true;
                for (int t = i - k + 1; t < i; ++t) {
                    if (names[j] == ans[t]) {
                        ok = false;
                        break;
                    }
                }
                if (ok) {
                    ans[i] = names[j];
                    break;
                }
            }
        } else {
            ans[i] = ans[i - (k - 1)];
        }
    }

    for (int i = 0; i < n; ++i) {
        cout << ans[i] << ' ';
    }
    cout << endl;
}