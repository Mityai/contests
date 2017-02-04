#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

int main() {
    freopen("stones.dat", "r", stdin);
    freopen("stones.sol", "w", stdout);

    int n, m;
    scanf("%d%d", &n, &m);

    set< pair<int, int> > mins;
    vector< set<int> > all(m);
    for (int i = 0; i < n; i++) {
        int t;
        scanf("%d", &t);

        if (t == 1) {
            int v, w;
            scanf("%d%d", &v, &w);
            --v;
            if (all[v].empty()) {
                mins.insert({w, v});
            } else if (*all[v].begin() > w) {
                mins.erase({*all[v].begin(), v});
                mins.insert({w, v});
            }
            all[v].insert(w);
        } else {
            auto del = mins.rbegin();
            int id = del->se;
            int w = del->fi;
            mins.erase(--mins.end());
            printf("%d\n", w);
            all[id].erase(w);
            mins.insert({*all[id].begin(), id});
        }
    }
}
