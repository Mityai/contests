#include <bits/stdc++.h>
using namespace std;

const double pi = acos(-1);
const double eps = 1e-5;

struct Point {
    double x, y;

    void in() {
        scanf("%lf%lf", &x, &y);
    }
};

bool operator == (const Point& pt1, const Point& pt2) {
    return fabs(pt1.x - pt2.x) < eps && fabs(pt1.y - pt2.y) < eps;
}

Point operator + (const Point& pt1, const Point& pt2) {
    return Point({pt1.x + pt2.x, pt1.y + pt2.y});
}

Point operator - (const Point& pt1, const Point& pt2) {
    return Point({pt1.x - pt2.x, pt1.y - pt2.y});
}

struct Line {
    double a, b, c;
    Line(const Point& pt1, const Point& pt2) {
        a = pt2.y - pt1.y;
        b = pt1.x - pt2.x;
        c = -a * pt1.x - b * pt1.y;
    }
};

Point intersect(const Line& ln1, const Line& ln2) {
    double det = ln1.a * ln2.b - ln2.a * ln1.b;
    double x = -(ln1.c * ln2.b - ln2.c * ln1.b) / det;
    double y = -(ln1.a * ln2.c - ln2.a * ln1.c) / det;
    return Point({x, y});
}

void rotate(Point& pt, double ang) {
    double x = pt.x * cos(ang) - pt.y * sin(ang);
    double y = pt.x * sin(ang) + pt.y * cos(ang);
    pt.x = x, pt.y = y;
}

double dist(const Point& pt) {
    return sqrt(pt.x * pt.x + pt.y * pt.y);
}

double operator & (const Point& pt1, const Point& pt2) {
    return pt1.x * pt2.y - pt1.y * pt2.x;
}

int main() {
    Point A, B, C;
    A.in(), B.in(), C.in();
    Line ln1(A, B), ln2(B, C);
    Point m1 = (A + B); m1.x /= 2, m1.y /= 2;
    Point m2 = (B + C); m2.x /= 2, m2.y /= 2;
    Point m11 = m1 + Point({ln1.a, ln1.b});
    Point m22 = m2 + Point({ln2.a, ln2.b});
    Line perp1(m1, m11), perp2(m2, m22);
    Point O = intersect(perp1, perp2);
    A = A - O, B = B - O, C = C - O;
    double ang = -atan2(A.y, A.x);
    rotate(A, ang), rotate(B, ang), rotate(C, ang);
    double rad = dist(A);

    double ans = 1e18;
    for (int n = 3; n <= 100; ++n) {
        bool ok1 = false, ok2 = false, ok3 = false;
        double area = 0.0;
        for (int j = 0; j < n; ++j) {
            double phi = 2 * j * pi / n;
            Point cur({rad * cos(phi), rad * sin(phi)});
            double prevphi = 2 * (j - 1) * pi / n;
            Point prev({rad * cos(prevphi), rad * sin(prevphi)});
            area += (cur & prev);
            if (cur == A) ok1 = true;
            if (cur == B) ok2 = true;
            if (cur == C) ok3 = true;
        }
        if (ok1 && ok2 && ok3) {
            ans = min(ans, fabs(area) / 2);
        }
    }
    printf("%.10lf\n", ans);
}
