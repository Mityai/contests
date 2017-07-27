#include <bits/stdc++.h>
using namespace std;

const int INF = INT_MAX;

int main() {
    freopen("people.in", "r", stdin);
    freopen("people.out", "w", stdout);

    int n;
    scanf("%d", &n);

    map<int, vector<pair<int, int>>> mp;
    for (int i = 0; i < n; ++i) {
        int a, b;
        scanf("%d%d", &a, &b);
        mp[a].push_back({b, i});
    }

    vector<int> d(n + 1, INF);
    vector<int> p(n + 1, -1);
    vector<int> num(n + 1, -1);
    d[0] = 0;
    for (auto& v : mp) {
        sort(v.second.begin(), v.second.end());
        vector<int> to(v.second.size());
        for (int i = 0; i < v.second.size(); ++i) {
            int x = v.second[i].first;
            to[i] = lower_bound(d.begin(), d.end(), x) - d.begin();
        }
        for (int i = (int)to.size() - 1; i >= 0; --i) {
            if (d[to[i]] > v.second[i].first) {
                d[to[i]] = v.second[i].first;
                num[to[i]] = v.second[i].second;
                p[num[to[i]]] = num[to[i] - 1];
            }
        }
    }

    int ans = 0;
    for (int i = 0; i <= n; ++i) if (d[i] != INF) ans = i;
    printf("%d\n", ans);
    vector<int> mem;
    int v = num[ans];
    while (v != -1) {
        mem.push_back(v);
        v = p[v];
    }
    for (int x : mem) {
        printf("%d ", x + 1);
    }
    puts("");
}
