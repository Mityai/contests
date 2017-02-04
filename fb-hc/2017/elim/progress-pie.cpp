#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

using Point = pair<int, int>;

const int C = 50;
const double pi = atan2(0, -1);

const vector<string> ans = {"white", "black"};

int dist(Point a) {
    return a.fi * a.fi + a.se * a.se;
}

int main() {
    int t;
    scanf("%d", &t);

    for (int i = 1; i <= t; ++i) {
        int P;
        Point pt;
        scanf("%d%d%d", &P, &pt.fi, &pt.se);
        pt.fi -= C;
        pt.se -= C;

        double ang = atan2(pt.se, pt.fi) + pi;
        ang = 2 * pi - ang;
        ang -= pi / 2;
        if (ang < 0) {
            ang += 2 * pi;
        }

        bool black = (ang * 100 <= P * 2 * pi && dist(pt) <= 2500);

        printf("Case #%d: %s\n", i, ans[black].c_str());
    }
}
