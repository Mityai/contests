#include <bits/stdc++.h>
#define Vector Point
using namespace std;

double sqr(double x) {
    return x * x;
}

struct Point {
    int x, y;

    Point() {}
    Point(int x, int y) : x(x), y(y) {}
    void in() {
        scanf("%d%d", &x, &y);
    }
};

Vector operator - (Vector vc1, Vector vc2) {
    return Vector(vc1.x - vc2.x, vc1.y - vc2.y);
}

double operator & (Vector vc1, Vector vc2) {
    return vc1.x * vc2.y - vc1.y * vc2.x;
}

double operator * (Vector vc1, Vector vc2) {
    return vc1.x * vc2.x + vc1.y * vc2.y;
}

double dist(Point pt1, Point pt2) {
    return sqrt(sqr(pt1.x - pt2.x) + sqr(pt1.y - pt2.y));
}

struct Segment {
    double a, b, c;
    Point pt1, pt2;

    Segment() {}
    Segment(Point pt1, Point pt2) : pt1(pt1), pt2(pt2) {
        a = pt2.y - pt1.y;
        b = pt1.x - pt2.x;
        c = -a * pt1.x - b * pt1.y;
    }
    double distance(Point pt) {
        if (((pt - pt1) * (pt2 - pt1)) >= 0 &&
            ((pt - pt2) * (pt1 - pt2)) >= 0) {
            return fabs(a * pt.x + b * pt.y + c) / sqrt(sqr(a) + sqr(b));
        }
        return min(dist(pt, pt1), dist(pt, pt2));
    }
};

int main() {
    freopen("distance.in", "r", stdin);
    freopen("distance.out", "w", stdout);

    Point A, B, C, D;
    A.in();
    B.in();
    C.in();
    D.in();

    Segment sAB(A, B);
    Segment sCD(C, D);

    double ans = min(min(sAB.distance(C), sAB.distance(D)), min(sCD.distance(A), sCD.distance(B)));
    if (((A - B) & (C - D)) != 0) {
        Vector BC = C - B;
        Vector BA = A - B;
        Vector BD = D - B;
        Vector CA = A - C;
        Vector CD = D - C;
        Vector CB = B - C;
        if ((BC & BA) * (BD & BA) <= 0 && (CA & CD) * (CB & CD) <= 0) {
            puts("0.0000000000");
            return 0;
        }
    }

    printf("%.10f\n", ans);
}
