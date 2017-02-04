#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

using ll = long long;

int main() {
    int n, m;
    scanf("%d%d", &n, &m);

    vector<int> p(n);
    unordered_map<int, vector<int>> comps;
    for (int i = 0; i < n; i++) {
        scanf("%d", &p[i]);
        comps[p[i]].push_back(i);
    }

    vector<int> s(m);
    for (int i = 0; i < m; i++) {
        scanf("%d", &s[i]);
    }

    vector<int> a(m), b(n);
    vector<char> used(m, false);
    bool ok = true;
    int cnt = 0;
    ll c = 0, u = 0;
    while (ok) {
        ok = false;
        for (int i = 0; i < m; i++) {
            if (s[i] != 1) {
                ok = true;
            }
            if (!comps[s[i]].empty() && used[i] == false) {
                int v = comps[s[i]].back();
                a[i] = cnt;
                b[v] = i + 1;
                used[i] = true;
                c++;
                u += cnt;
                comps[s[i]].pop_back();
            }
            s[i] = (s[i] + 1) / 2;
        }
        cnt++;
    }

    printf("%lld %lld\n", c, u);
    for (int x : a) {
        printf("%d ", x);
    }
    puts("");
    for (int x : b) {
        printf("%d ", x);
    }
    puts("");
}
