#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

int main() {
#if __APPLE__
    freopen("B.in", "r", stdin);
    freopen("B.out", "w", stdout);
#endif

    ios_base::sync_with_stdio(false);

    int n, m;
    while (cin >> n >> m) {
        vector< priority_queue< pair< int, string > > > q(m + 1);
        for (int i = 0; i < n; i++) {
            string name;
            int r, x;
            cin >> name >> r >> x;
            q[r].push({x, name});
        }

        for (int i = 1; i <= m; i++) {
            string name1 = q[i].top().se;
            int x1 = q[i].top().fi;
            q[i].pop();
            string name2 = q[i].top().se;
            int x2 = q[i].top().fi;
            q[i].pop();
            if (!q[i].empty()) {
                if (q[i].top().fi == x2) {
                    cout << "?" << endl;
                    continue;
                }
            }
            cout << name1 << ' ' << name2 << endl;
        }
    }
}
