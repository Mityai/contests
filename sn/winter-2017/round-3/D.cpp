#include <bits/stdc++.h>
#define x first
#define y second
#define fi first
#define se second
using namespace std;

int dist(int x1, int y1) {
    return x1 * x1 + y1 * y1;
}

int main() {
    vector<pair<int, int>> pts(3);
    for (int i = 0; i < 3; ++i) {
        scanf("%d%d", &pts[i].fi, &pts[i].se);
    }

    sort(pts.begin(), pts.end());

    do {
        int x1 = pts[1].x - pts[0].x;
        int y1 = pts[1].y - pts[0].y;
        int x2 = pts[2].x - pts[0].x;
        int y2 = pts[2].y - pts[0].y;
        int x3 = pts[2].x - pts[1].x;
        int y3 = pts[2].y - pts[1].y;
        if (dist(x1, y1) + dist(x2, y2) == dist(x3, y3)) {
            cout << pts[0].fi + x1 + x2 << ' ' << pts[0].se + y1 + y2 << endl;
            return 0;
        }
    } while (next_permutation(pts.begin(), pts.end()));
}
