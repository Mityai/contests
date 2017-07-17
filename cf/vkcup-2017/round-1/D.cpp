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

    int n;
    cin >> n;

    string s;
    cin >> s;

    int swaps = 0;
    while (true) {
        int p = -1;
        for (int i = n - 1; i >= 1; --i) {
            if (s[i - 1] == 'V' && s[i] == 'K') {
                p = i;
                break;
            }
        }
        if (p == -1) {
            break;
        }
        int right = toright(s, p);
        int left = roleft(s, p);
        if (right <= left) {
            for (int i = p; i < p + right; ++i) {
                swap(s[i], s[i + 1]);
            }
        } else {
            for (int i = p; i >= p - left + 1; --i) {
                swap(s[i], s[i - 1]);
            }
        }
    }

    cout << swaps << endl;
}
