#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

using ll = long long;

int main() {
#if __APPLE__
    freopen("I.in", "r", stdin);
    freopen("I.out", "w", stdout);
#endif

    int n;
    scanf("%d", &n);

    queue<int> q;
    for (int i = 0; i < n; ++i) {
        int x;
        scanf("%d", &x);
        q.push(x);
    }

    ll petya = 0, gena = 0;
    int step = 0;
    while (q.size() >= 2) {
        ll cur = 0;
        cur += q.front();
        q.pop();
        cur += q.front();
        q.pop();
        while (!q.empty() && q.front() >= 0) {
            cur += q.front();
            q.pop();
        }
        cout << petya << ' ' << gena << '\n';
        if (step == 0) {
            petya += cur;
        } else {
            gena += cur;
        }
        step = 1 - step;
        q.push(cur);
    }

    printf("%lld\n", petya - gena);
}
