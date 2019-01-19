#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T>
bool has(const map<ll, T>& once, ll x) {
    return once.find(x) != once.end();
}

void insert(map<ll, int>& once, map<ll, set<int>>& more, ll x, int pos) {
    if (has(once, x)) {
        more[x].insert(once[x]);
        once.erase(x);
        more[x].insert(pos);
    } else if (has(more, x)) {
        more[x].insert(pos);
    } else {
        once[x] = pos;
    }
}

int main() {
    int n;
    scanf("%d", &n);

    map<ll, int> once;
    map<ll, set<int>> more;

    for (int i = 0; i < n; ++i) {
        int x;
        scanf("%d", &x);
        insert(once, more, x, i);
    }

    while (!more.empty()) {
        ll x = more.begin()->first;
        set<int>& poses = more.begin()->second;

        poses.erase(poses.begin());
        insert(once, more, 2 * x, *poses.begin());
        poses.erase(poses.begin());
        if (poses.empty()) {
            more.erase(more.begin());
        } else if (poses.size() == 1) {
            once[x] = *poses.begin();
            more.erase(more.begin());
        }
    }

    map<int, ll> poses;
    for (auto& v : once) {
        poses[v.second] = v.first;
    }

    printf("%d\n", static_cast<int>(poses.size()));
    for (auto& v : poses) {
        printf("%lld ", v.second);
    }
    putchar('\n');
}
