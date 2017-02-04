#include <iostream>
#include <cstdio>
#include <climits>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <algorithm>

typedef long long ll;

using namespace std;

struct Point {
    ll x, y;

    void in() {
        scanf("%lld%lld", &x, &y);
    }

    Point() {};
    Point(ll _x, ll _y) {
        x = _x;
        y = _y;
    }

    Point operator - (const Point &pt) {
        return Point(x - pt.x, y - pt.y);
    }

    bool operator == (const Point &pt) {
        return x == pt.x && y == pt.y;
    }

    bool operator < (const Point &pt) {
        return x < pt.x || (x == pt.x && y < pt.y);
    }
};

ll vect(Point pt, Point pt1, Point pt2) {
    return (pt1.x - pt.x) * (pt2.y - pt.y) - (pt2.x - pt.x) * (pt1.y - pt.y);
}

bool pt_in(Point pt, Point pt1, Point pt2) {
    return (vect(pt, pt1, pt2) <= 0 && vect(pt, pt2, Point(0, 0)) <= 0 && vect(pt, Point(0, 0), pt1) <= 0) ||
           (vect(pt, pt1, pt2) >= 0 && vect(pt, pt2, Point(0, 0)) >= 0 && vect(pt, Point(0, 0), pt1) >= 0);
}

int main() {
    freopen("theodore.in", "r", stdin);
    freopen("theodore.out", "w", stdout);

    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);

    vector<Point> pts(n);
    Point z;
    int z_pos = 0;

    for (int i = 0; i < n; i++) {
        pts[i].in();

        if (i == 0) {
            z = pts[i];
        } else if (pts[i] < z) {
            z = pts[i];
            z_pos = i;
        }
    }

    rotate(pts.begin(), pts.begin() + z_pos, pts.end());
    pts.erase(pts.begin());
    --n;

    vector<double> ang(n);
    for (int i = 0; i < pts.size(); i++) {
        pts[i] = pts[i] - z;
        ang[i] = atan2(double(pts[i].y), double(pts[i].x));
    }


    int cnt = 0;
    for (int i = 0; i < m; i++) {
        Point pt;
        pt.in();
        pt = pt - z;

        bool in = false;

        if (pt == Point(0, 0)) {
            in = true;
        } else {
            if (pt.x >= 0) {
                vector<double>::iterator it = 
                upper_bound(ang.begin(), ang.end(), atan2(double(pt.y), double(pt.x)));

                if (it == ang.end() && pt == pts.back()) {
                    --it;
                }

                if (it != ang.begin() && it != ang.end()) {
                    int j = it - ang.begin();
                    if (pt_in(pt, pts[j - 1], pts[j])) {
                        in = true;
                    }
                }
            }
        }

        if (in) {
            ++cnt;
        }
    }

    if (cnt >= k) {
        printf("YES\n");
    } else {
        printf("NO\n");
    }
}