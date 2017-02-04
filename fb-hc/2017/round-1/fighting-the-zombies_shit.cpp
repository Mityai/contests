#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-6;

bool larger(double a, double b) {
    return a > b + eps;
}

bool eq(double a, double b) {
    return fabs(a - b) < eps;
}

double sqr(double x) {
    return x * x;
}

struct Point {
    double x, y;

    Point() {
    }

    Point(double x, double y) : x(x), y(y) {
    }

    void in() {
        scanf("%lf%lf", &x, &y);
    }
};

double sqrdist(Point pt1, Point pt2) {
    return sqr(pt1.x - pt2.x) + sqr(pt1.y - pt2.y);
}

Point middle(Point pt1, Point pt2) {
    return Point((pt1.x + pt2.x) / 2, (pt1.y + pt2.y) / 2);
}

struct Line {
    double a, b, c;

    Line() {
    }

    Line(Point pt1, Point pt2) {
        a = pt2.y - pt1.y;
        b = pt1.x - pt2.x;
        c = -a * pt1.x - b * pt1.y;
    }

    Point intersect(Line ln) {
        double z = a * ln.b - b * ln.a;
        double x = -(c * ln.b - ln.c * b) / z;
        double y = -(a * ln.c - ln.a * c) / z;
        return Point(x, y);
    }

    bool equal(Line ln) {
        return eq(a * ln.b - b * ln.a, 0);
    }
};

Line per_bis(Point pt1, Point pt2) {
    Line ln(pt1, pt2);
    Point mid(middle(pt1, pt2));
    Point vec(mid.x + ln.a, mid.y + ln.b);
    return Line(mid, vec);
}

bool cmp(Point pt1, Point pt2) {
    return pt1.x < pt2.x;
}

int n;
double R;
vector<Point> pts;

int main() {
    int t;
    scanf("%d", &t);

    for (int test = 1; test <= t; ++test) {
        scanf("%d%lf", &n, &R);

        pts.resize(n);
        for (int i = 0; i < n; ++i) {
            pts[i].in();
        }

        sort(pts.begin(), pts.end(), cmp);

        // TODO 1 or 2 points

        int ans = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                for (int k = j + 1; k < n; k++) {
                    Line bis1(pts[i], pts[j]);
                    Line bis2(pts[i], pts[k]);
                    if (bis1.equal(bis2)) {
                        continue;
                    }
                    Point O(bis1.intersect(bis2));
                    double sqr_r = sqrdist(O, pts[i]);
                    if (larger(sqr_r, 2 * sqr(R))) {
                        continue;
                    }
                }
            }
        }
    }
}
