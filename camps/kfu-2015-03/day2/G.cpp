#include <bits/stdc++.h>
#define Vector Point
using namespace std;

const double eps = 1e-9;

bool Less(double a, double b) {
    return a + eps < b;
}

bool More(double a, double b) {
    return Less(b, a);
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
    void norm() {
        double z = sqrt(sqr(x) + sqr(y));
        x /= z;
        y /= z;
    }
    bool equal(Point pt) {
        return Equal(x, pt.x) && Equal(y, pt.y);
    }
    void in() {
        scanf("%lf%lf", &x, &y);
    }
    void out() {
        printf("%.10lf %.10lf\n", x, y);
    }
};

Vector operator - (Vector vc1, Vector vc2) {
    return Vector(vc1.x - vc2.x, vc1.y - vc2.y);
}

Vector operator + (Vector vc1, Vector vc2) {
    return Vector(vc1.x + vc2.x, vc1.y + vc2.y);
}

Vector operator * (Vector vc, double x) {
    return Vector(vc.x * x, vc.y * x);
}

double distance(Point pt1, Point pt2) {
    return sqrt(sqr(pt1.x - pt2.x) + sqr(pt1.y - pt2.y));
}

struct Circle {
    Point pt;
    double R;

    Circle() {}
    Circle(Point pt, double R) : pt(pt), R(R) {}
    void in() {
        pt.in();
        scanf("%lf", &R);
    }
};

void intersect(Circle cir1, Circle cir2) {
    double R1 = cir1.R, R2 = cir2.R;
    Point O1 = cir1.pt, O2 = cir2.pt;
    double l = distance(O1, O2);

    if (Equal(R1, R2) && O1.equal(O2)) {
        puts("3");
        return;
    }

    if (Less(R1 + R2, l) || Less(R1 + l, R2) || Less(R2 + l, R1)) {
        puts("0");
        return;
    }

    double cosA = (sqr(R1) + sqr(l) - sqr(R2)) / (2 * R1 * l);
    double dO1H = R1 * cosA;
    Vector OH = O2 - O1;
    OH.norm();
    OH = OH * dO1H;
    Point H = O1 + OH;

    if (Equal(l, R1 + R2) || Equal(l + R1, R2) || Equal(l + R2, R1)) {
        puts("1");
        H.out();
        return;
    }

    double dHP = sqrt(max(0.0, sqr(R1) - sqr(dO1H)));
    Vector OO = O2 - O1;
    Vector HP = Vector(-OO.y, OO.x);
    HP.norm();
    HP = HP * dHP;
    Point P1 = H + HP;
    Point P2 = H - HP;

    puts("2");
    H.out();
    printf("%.10lf %.10lf\n", fabs(dO1H), dHP);
    P1.out();
    P2.out();
}

int main() {
    freopen("intersec.in", "r", stdin);
    freopen("intersec.out", "w", stdout);

    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        Circle cir1, cir2;
        cir1.in();
        cir2.in();
        intersect(cir1, cir2);
    }
}
