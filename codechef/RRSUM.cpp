#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ll n, m;
    scanf("%lld%lld", &n, &m);

    for (int i = 0; i < m; i++) {
        ll q;
        scanf("%lld", &q);

        ll st, en;
        {
            ll lb = 0, rb = n + 1;
            while (lb + 1 < rb) {
                ll mb = (lb + rb) / 2;
                if (mb + 2 * n < q) {
                    lb = mb;
                } else {
                    rb = mb;
                }
            }
            st = rb;
        }
        {
            ll lb = 0, rb = n + 1;
            while (lb + 1 < rb) {
                ll mb = (lb + rb) / 2;
                if (mb + n + 1 > q) {
                    rb = mb;
                } else {
                    lb = mb;
                }
            }
            en = lb;
        }

        printf("%lld\n", max(0LL, en - st + 1));
    }
}
