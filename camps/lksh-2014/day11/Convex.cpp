#include <iostream>
#include <cstdio>
#include <climits>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <algorithm>

typedef long long ll;

using namespace std;

double sqr(double x) {
    return x * x;
}

struct Point {
    double x, y;
    int n;

    void input() {
        scanf("%lf%lf", &x, &y);
    }

    void output() {
        printf("%d ", n);
    }

    Point() {};
    Point(double _x, double _y, int _n) {
        x = _x;
        y = _y;
        n = _n;
    }

    Point operator - (const Point &pt) {
        return Point(x - pt.x, y - pt.y, n);
    }

    bool operator == (const Point &pt) {
        return x == pt.x && y == pt.y;
    }
};

struct Vect {
    double x, y;

    void input() {
        scanf("%lf%lf", &x, &y);
    }

    Vect() {};
    Vect(Point pt1, Point pt2) {
        x = pt2.x - pt1.x;
        y = pt2.y - pt1.y;
    }
};

double operator & (const Vect &vc1, const Vect &vc2) {
    return vc1.x * vc2.y - vc2.x * vc1.y;
}

double dist(Point pt1, Point pt2) {
    return sqrt(sqr(pt1.x - pt2.x) + sqr(pt1.y - pt2.y));
}

ll getArea(Point pt1, Point pt2) {
    return ll(pt1.x * pt2.y) - ll(pt1.y * pt2.x);
}

bool cmp_pol(Point pt1, Point pt2) {
    return atan2(pt1.y, pt1.x) < atan2(pt2.y, pt2.x) ||
          (atan2(pt1.y, pt1.x) == atan2(pt2.y, pt2.x) && pt1.x < pt2.x) ||
          (atan2(pt1.y, pt1.x) == atan2(pt2.y, pt2.x) && pt1.x == pt2.x && pt1.y < pt2.y);
}

int main() {
    freopen("convex.in", "r", stdin);
    freopen("convex.out", "w", stdout);

    int n;
    scanf("%d", &n);

    vector<Point> pts(n);

    Point z;

    for (int i = 0; i < n; i++) {
        pts[i].input();
        pts[i].n = i + 1;

        if (i == 0) {
            z = pts[i];
        }

        if (pts[i].x < z.x || (pts[i].x == z.x && pts[i].y < z.y)) {
            z = pts[i];
        }
    }

    for (int i = 0; i < n; i++) {
        pts[i] = pts[i] - z;
    }

    sort(pts.begin(), pts.end(), cmp_pol);

    vector<Point> convex(1, Point(0, 0, z.n));
    int sz = 1;
    for (int i = 0; i < pts.size(); i++) {
        if (pts[i].n == z.n) {
            continue;
        }

        if (sz < 2) {
            convex.push_back(pts[i]);
            ++sz;
            continue;
        }

        while (sz > 1) {
            if ((Vect(convex[sz - 1], convex[sz - 2]) & Vect(convex[sz - 1], pts[i])) < 0) {
                break;
            }

            convex.pop_back();
            --sz;
        }

        convex.push_back(pts[i]);
        ++sz;
    }

    double pr = 0;
    ll sq = 0;

    printf("%d\n", (int)convex.size());
    for (int i = 0; i < convex.size(); i++) {
        convex[i].output();

        if (i > 0) {
            pr += dist(convex[i], convex[i - 1]);
            sq += getArea(convex[i - 1], convex[i]);
        } else {
            pr += dist(convex[0], convex[sz - 1]);
            sq += getArea(convex[sz - 1], convex[0]);
        }
    }
    printf("\n");

    printf("%.12lf\n%lld", pr, abs(sq) / 2);

    if (sq % 2) {
        printf(".5\n");
    }
}