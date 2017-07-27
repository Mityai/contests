#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct Fenwick {
    int n;
    vector<int> fenw;

    Fenwick(int n) : n(n), fenw(n) {
    }

    void add(int pos, int val) {
        for (int i = pos; i < n; i = (i | (i + 1))) {
            fenw[i] += val;
        }
    }

    int sum(int pos) {
        int ret = 0;
        for (int i = pos; i >= 0; i = (i & (i + 1)) - 1) {
            ret += fenw[i];
        }
        return ret;
    }

    int sum(int l, int r) {
        int ret = sum(r);
        if (l > 0) ret -= sum(l - 1);
        return ret;
    }
};

int main() {
    int n;
    scanf("%d", &n);

    map<int, int> last;
    vector<pair<int, int>> pos;
    for (int i = 0; i < n; ++i) {
        int x;
        scanf("%d", &x);
        if (last.find(x) != last.end()) {
            pos.push_back({last[x], i});
        } else {
            last[x] = i;
        }
    }

    Fenwick f(n);
    ll ans = 0;
    sort(pos.begin(), pos.end());
    for (int i = 0; i < n / 2; ++i) {
        int x = pos[i].first;
        int y = pos[i].second;
        ans += y - x - 1 - f.sum(x, y);
        f.add(y, 1);
    }
    printf("%lld\n", ans);
}
