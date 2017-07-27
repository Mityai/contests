#include <bits/stdc++.h>
#define Point Vector
using namespace std;

const double eps = 1e-5;

inline double sqr(double x) {
    return x * x;
}

inline bool ge(double x, double y) {
    return x > y + eps;
}

inline bool le(double x, double y) {
    return x < y - eps;
}

inline bool eq(double x, double y) {
    return fabs(x - y) < eps;
}

struct Vector {
    double x, y;

    void scan() {
        scanf("%lf%lf", &x, &y);
    }

    double len() const {
        return sqrt(sqr(x) + sqr(y));
    }
};

Vector operator + (const Vector& v1, const Vector& v2) {
    return Vector({v1.x + v2.x, v1.y + v2.y});
}

Vector operator - (const Vector& v1, const Vector& v2) {
    return Vector({v1.x - v2.x, v1.y - v2.y});
}

Vector operator * (const Vector& v1, double lambda) {
    return Vector({lambda * v1.x, lambda * v1.y});
}

Vector operator * (double lambda, const Vector& v1) {
    return v1 * lambda;
}

Vector operator / (const Vector& v1, double lambda) {
    return Vector({v1.x / lambda, v1.y / lambda});
}

struct Line {
    double a, b, c;

    Line(const Point& pt1, const Point& pt2) {
        a = pt2.y - pt1.y;
        b = pt1.x - pt2.x;
        c = -a * pt1.x - b * pt1.y;
        double n = Vector({a, b}).len();
        a /= n;
        b /= n;
        c /= n;
    }

    Vector norm() const {
        return Vector({a, b});
    }

    Vector dir() const {
        return Vector({-b, a});
    }
};

double dist(const Point& pt1, const Point& pt2) {
    return (pt1 - pt2).len();
}

double dist(const Line& ln, const Point& pt) {
    return ln.a * pt.x + ln.b * pt.y + ln.c;
}

struct Circle {
    Point O;
    double r;

    void scan() {
        O.scan();
        scanf("%lf", &r);
    }
};

vector<Point> intersect(const Circle& c1, const Circle& c2) {
    double d = dist(c1.O, c2.O);
    if (ge(d, c1.r + c2.r)) return {};
    if (le(c1.r + d, c2.r)) return {};
    if (le(c2.r + d, c1.r)) return {};
    double h = (sqr(c1.r) + sqr(d) - sqr(c2.r)) / (2 * d);
    Vector O1O2 = c2.O - c1.O;
    Point H = c1.O + O1O2 * h / O1O2.len();
    double l = sqrt(sqr(c1.r) - sqr(h));
    vector<Point> ret;
    ret.push_back(H + l * Line(c1.O, c2.O).norm());
    if (!eq(d, c1.r + c2.r)) {
        ret.push_back(H - l * Line(c1.O, c2.O).norm());
    }
    return ret;
}

vector<Point> intersect(const Circle& cr, const Line& ln) {
    double d = dist(ln, cr.O);
    if (ge(d, cr.r)) return {};
    Point M = cr.O + d * ln.norm();
    Point N = cr.O - d * ln.norm();
    if (le(dist(ln, N), dist(ln, M))) {
        M = N;
    }
    double h = sqrt(sqr(cr.r) - sqr(d));
    vector<Point> ret;
    ret.push_back(M + h * ln.dir());
    if (!eq(d, cr.r)) {
        ret.push_back(M - h * ln.dir());
    }
    return ret;
}

vector<Point> intersect(const Line& ln1, const Line& ln2) {
    double det = ln1.a * ln2.b - ln1.b * ln2.a;
    double x = -(ln1.c * ln2.b - ln1.b * ln2.c) / det;
    double y = -(ln1.a * ln2.c - ln1.c * ln2.a) / det;
    return {{x, y}};
}

Line perp_bis(const Point& pt1, const Point& pt2) {
    Point M = (pt1 + pt2) / 2;
    Point N = M + Line(pt1, pt2).norm();
    return Line(M, N);
}

Circle get_circle(Circle c1, Circle c2) {
    if (le(c2.r, c1.r)) swap(c1, c2);
    const Vector N = c2.O - c1.O;
    Point P1 = c1.O + N / N.len() * (c1.r * N.len()) / (c1.r + c2.r);
    double R1 = (c1.r / c2.r) * N.len() / (1 - c1.r / c2.r);
    Point P2 = c1.O - N / N.len() * R1;
    Point O = (P1 + P2) / 2;
    double r = dist(O, P1);
    return Circle({O, r});
}

double get_angle(const Circle& cr, const Point& pt) {
    double d = dist(cr.O, pt);
    return 2 * asin(cr.r / d);
}

int main() {
#if __APPLE__
    freopen("C.in", "r", stdin);
    freopen("C.out", "w", stdout);
#endif

    Circle c1, c2, c3;
    c1.scan();
    c2.scan();
    c3.scan();

    vector<Point> tosee;
    if (eq(c1.r, c2.r) && eq(c1.r, c3.r)) {
        tosee = intersect(perp_bis(c1.O, c2.O), perp_bis(c1.O, c3.O));
    } else if (eq(c1.r, c2.r) && !eq(c1.r, c3.r)) {
        tosee = intersect(get_circle(c1, c3), perp_bis(c1.O, c2.O));
    } else if (!eq(c1.r, c2.r) && eq(c1.r, c3.r)) {
        tosee = intersect(get_circle(c1, c2), perp_bis(c1.O, c3.O));
    } else {
        tosee = intersect(get_circle(c1, c2), get_circle(c1, c3));
    }

    if (!tosee.empty()) {
        auto ans = tosee[0];
        for (auto& v : tosee) {
            if (le(get_angle(c1, ans), get_angle(c1, v))) {
                ans = v;
            }
        }
        printf("%.10lf %.10lf\n", ans.x, ans.y);
    }
}
