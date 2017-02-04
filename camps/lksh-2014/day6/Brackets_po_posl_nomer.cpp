#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>

typedef long long ll;

using namespace std;

const int MAXN = 50;

ll d[MAXN][MAXN];

int main() {
    freopen("brackets2num.in", "r", stdin);
    freopen("brackets2num.out", "w", stdout);

    string s;
    cin >> s;

    int n = (int)s.length();

    d[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int b = 0; b <= i; b++) {
            if (b == 0) {
                d[i][b] = d[i - 1][b + 1];
            } else if (b == i) {
                d[i][b] = d[i - 1][b - 1];
            } else {
                d[i][b] = d[i - 1][b - 1] + d[i - 1][b + 1];
            }
        }
    }

    ll ans = 0, b = 1;
    for (int i = 2; i <= n; i++) {
        ll m = d[n - i][b + 1];
        if (s[i - 1] == ')') {
            ans += m;
            --b;
        } else {
            ++b;
        }
    }

    printf("%lld\n", ans);
}