#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

const int MOD = 1e9 + 7;
const int N = 1e6 + 2;

char s[N];

int add(ll a, ll b) {
    return (a + b) % MOD;
}

int main() {
#if __APPLE__
    //freopen("B.in", "r", stdin);
    //freopen("B.out", "w", stdout);
#endif

    scanf("%s", s);
    int n = strlen(s);

    int ans = 0;
    int cntb = 0;
    for (int i = n - 1; i >= 0; --i) {
        if (s[i] == 'a') {
            ll len = (cntb + ans) % MOD;
            ans = add(ans, len) % MOD;
        } else ++cntb;
    }

    printf("%d\n", ans);
}
