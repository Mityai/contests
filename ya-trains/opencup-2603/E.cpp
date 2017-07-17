#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    scanf("%d", &t);

    for (int test = 0; test < t; ++test) {
        int n, m;
        scanf("%d%d", &n, &m);

        vector<vector<int>> ga(n), gb(n);
        vector<int> in(n);
        for (int i = 0; i < m; ++i) {
            int a, b;
            char c;
            scanf("%d %c %d", &a, &c, &b);
            --a, --b;

            if (c == '<') {
                gb[b].push_back(a);
                ++in[a];
            } else {
                ga[a].push_back(b);
            }
        }

        set<int> isol;
        bool lose = false;
        for (int i = 0; i < n; ++i) {
            if (ga[i].empty()) {
                if (in[i] != n) {
                    isol.insert(i);
                } else {
                    lose = true;
                }
            }
        }

        if (lose) {
            puts("LOSS");
            continue;
        }

        if (!isol.empty()) {
            for (int i = 0; i < n; ++i) {
                for (int x : gb[i]) {
                    isol.erase(x);
                }
            }

            if (isol.empty()) {
                puts("LOSS");
                continue;
            } else {
                puts("DRAW");
                continue;
            }
        }
    }
}
