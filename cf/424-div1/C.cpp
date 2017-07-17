#include <bits/stdc++.h>
#define div asdjkld
#define fi first
#define se second
using namespace std;

typedef long long ll;

const ll INF = 1e15;

ll get_next(const vector<ll>& a, const vector<ll>& need, ll lb) {
    ll rb = INF;
    for (int i = 0; i < a.size(); ++i) {
        ll cur = a[i] / need[i];
        rb = min(rb, max(lb, cur) + 1);
    }
    while (lb + 1 < rb) {
        ll mb = (lb + rb) / 2;
        bool ok = true;
        for (int j = 0; j < a.size(); ++j) {
            if (a[j] / mb >= need[j])
            if ((a[j] + mb - 1) / mb < need[j]) {
                ok = false;
                break;
            }
        }
        if (ok) lb = mb;
        else rb = mb;
    }
    return lb;
}

inline int readInt() {
    char c = getchar();
    while (c <= 32) c = getchar();
    int ret = 0;
    while ('0' <= c && c <= '9') ret = ret * 10 + c - '0', c = getchar();
    return ret;
}

inline ll readLong() {
    char c = getchar();
    while (c <= 32) c = getchar();
    ll ret = 0;
    while ('0' <= c && c <= '9') ret = ret * 10 + c - '0', c = getchar();
    return ret;
}

int main() {
#if __APPLE__
    freopen("C.in", "r", stdin);
    freopen("C.out", "w", stdout);
#endif

    while (true) {
        int n = readInt();
        ll k = readLong();
        vector<ll> a(n);
        for (int i = 0; i < n; ++i) {
            a[i] = readLong();
            k += a[i];
        }

        ll lb = 1, rb;
        vector<ll> d;
        while (true) {
            vector<ll> need(n);
            bool ones = true;
            for (int i = 0; i < n; ++i) {
                need[i] = (a[i] + lb - 1) / lb;
                if (need[i] != 1) ones = false;
            }
            rb = get_next(a, need, lb);
            d.push_back(lb);
            d.push_back(rb);
            if (ones) {
                d.push_back(rb + 1);
                d.push_back(INF);
                break;
            }
            lb = rb + 1;
        }

        ll ans = 1;
        for (int i = 0; i + 1 < d.size(); ++i) {
            ll sum = 0;
            for (int j = 0; j < n; ++j) {
                sum += (a[j] + d[i] - 1) / d[i];
            }
            ll lb = k / sum;
            if (d[i] <= lb && lb <= d[i + 1]) {
                ans = max(ans, lb);
            }
        }
        printf("%lld\n", ans);
        return 0;
    }
}
