#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

using ll = long long;

int main() {
#if __APPLE__
    freopen("B.in", "r", stdin);
    freopen("B.out", "w", stdout);
#endif

    ll fs, ft, t;
    scanf("%lld%lld%lld", &fs, &ft, &t);

    int n;
    scanf("%d", &n);

    vector<ll> tm(n);
    set<ll> q;
    q.insert(0);
    q.insert(fs);
    q.insert(max(0ll, fs - 1));
    for (int i = 0; i < n; ++i) {
        scanf("%lld", &tm[i]);
        q.insert(max(0ll, tm[i] - 1));
        q.insert(tm[i]);
    }
    q.insert(ft - t);

    sort(tm.begin(), tm.end());

    ll best = -1;
    ll cost = -1;

    set<ll> que;
    int i = 0;
    for (ll curtime : q) {
        while (!que.empty() && *que.begin() <= curtime) {
            que.erase(que.begin());
        }
        while (i < n && tm[i] == curtime) {
            if (que.empty()) {
                que.insert(max(fs, tm[i]) + t);
            } else {
                que.insert(max(tm[i], *que.rbegin()) + t);
            }
            ++i;
        }

        ll entime;
        ll wait;
        if (que.empty()) {
            if (curtime < fs) {
                entime = fs + t;
                wait = fs - curtime;
            } else {
                entime = curtime + t;
                wait = 0;
            }
        } else {
            ll last = *que.rbegin();
            entime = max(curtime, last) + t;
            wait = max(curtime, last) - curtime;
        }
        if (entime <= ft && (wait < cost || cost == -1)) {
            best = curtime;
            cost = wait;
        }
    }

    printf("%lld\n", best);
}
