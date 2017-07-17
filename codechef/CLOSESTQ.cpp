#include <bits/stdc++.h>
using namespace std;

int dist(pair<int, int> a, pair<int, int> b) {
    return (a.first - b.first) * (a.first - b.first) +
           (a.second - b.second) * (a.second - b.second);
}

int main() {
    int Q;
    scanf("%d", &Q);

    set<pair<int, int>> pts;
    multiset<int> closest;
    for (int q = 0; q < Q; ++q) {
        char c;
        int x, y;
        scanf(" %c%d%d", &c, &x, &y);
        if (c == '-') {
            pts.erase({x, y});
            for (auto& pt : pts) {
                closest.erase(closest.find(dist(pt, {x, y})));
            }
        } else {
            for (auto& pt : pts) {
                closest.insert(dist(pt, {x, y}));
            }
            pts.insert({x, y});
        }

        if (closest.empty()) {
            puts("0");
        } else {
            printf("%d\n", *closest.begin());
        }
    }
}
