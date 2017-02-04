#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

const int N = 2e5 + 123;

vector<ll> fenwA(N), fenwB(N);
ll A[N], B[N];

void add(int pos, int val, vector<ll> &fenw) {
    for (int i = pos; i < N; i = (i | (i + 1))) {
        fenw[i] += val;
    }
}

ll sum(int pos, vector<ll> &fenw) {
    ll ret = 0;
    for (int i = pos; i >= 0; i = (i & (i + 1)) - 1) {
        ret += fenw[i];
    }
    return ret;
}

int main() {

    int n, k, a, b, q;
    scanf("%d%d%d%d%d", &n, &k, &a, &b, &q);

    for (int i = 0; i < q; i++) {
        int t;
        scanf("%d", &t);

        if (t == 1) {
            int d, ai;
            scanf("%d%d", &d, &ai);

            ll addA = min(a - A[d], (ll)ai);
            A[d] += addA;
            add(d, addA, fenwA);
            ll addB = min(b - B[d], (ll)ai);
            B[d] += addB;
            add(d, addB, fenwB);
        } else {
            int p;
            scanf("%d", &p);
    
            ll ans = sum(p - 1, fenwB) + sum(N - 1, fenwA) - sum(p + k - 1, fenwA);
            printf("%lld\n", ans);
        }
    }
}
