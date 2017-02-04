#include <bits/stdc++.h>
#define Vector Point
using namespace std;

const double eps = 1e-9;

bool Less(double a, double b) {
    return a + eps < b;
}

bool Equal(double a, double b) {
    return fabs(a - b) < eps;
}

double sqr(double x) {
    return x * x;
}

struct Point {
    double x, y;

    Point() {}
    Point(double x, double y) : x(x), y(y) {}
    void in() {
        scanf("%lf%lf", &x, &y);
    }
    void out() {
        printf("%.10lf %.10lf\n", x, y);
    }

    void norm() {
        double z = sqrt(sqr(x) + sqr(y));
        x /= z;
        y /= z;
    }
};

double distance(Point pt1, Point pt2) {
    return sqrt(sqr(pt1.x - pt2.x) + sqr(pt1.y - pt2.y));
}

Vector operator + (Vector vc1, Vector vc2) {
    return Vector(vc1.x + vc2.x, vc1.y + vc2.y);
}

Vector operator - (Vector vc1, Vector vc2) {
    return Vector(vc1.x - vc2.x, vc1.y - vc2.y);
}

Vector operator * (Vector vc, double x) {
    return Vector(vc.x * x, vc.y * x);
}

struct Circle {
    Point pt;
    double R;

    void in() {
        pt.in();
        scanf("%lf", &R);
    }
};

void tangent(Circle cir, Point P1) {
    Point O = cir.pt;
    double R = cir.R;

    double l = distance(O, P1);
    if (Less(l, R)) {
        puts("0");
        return;
    }

    if (Equal(l, R)) {
        puts("1");
        P1.out();
        return;
    }

    double d = sqrt(sqr(l) - sqr(R));
    double dP1P3 = sqr(d) / l;

    Vector P1P0 = O - P1;
    P1P0.norm();
    Vector P1P3 = P1P0 * dP1P3;
    Point P3 = P1 + P1P3;

    double h = sqrt(sqr(d) - sqr(dP1P3));
    Vector P3P2 = Vector(-P1P0.y, P1P0.x) * h;

    Point P21 = P3 + P3P2;
    Point P22 = P3 - P3P2;

    puts("2");
    P3.out();
    printf("%.10lf %.10lf\n", dP1P3, h);
    P21.out();
    P22.out();
}

int main() {
    freopen("tangent.in", "r", stdin);
    freopen("tangent.out", "w", stdout);

    Circle cic;
    cic.in();

    Point pt;
    pt.in();

    tangent(cic, pt);
}
