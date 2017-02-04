#include <bits/stdc++.h>
#define Vector Point
using namespace std;

typedef long long ll;

const ll X = 1e9 + 7;
const ll Y = 1e9 + 9;

// TODO lld --> I64d

struct Point {
    ll x, y;

    Point() {}
    Point(ll x, ll y) : x(x), y(y) {}

    void in() {
        scanf("%lld%lld", &x, &y);
    }
};

Vector operator - (Vector vc1, Vector vc2) {
    return Vector(vc1.x - vc2.x, vc1.y - vc2.y);
}

ll operator & (Vector vc1, Vector vc2) {
    return vc1.x * vc2.y - vc1.y * vc2.x;
}

struct Segment {
    Point P1, P2;

    Segment() {}
    Segment(Point P1, Point P2) : P1(P1), P2(P2) {}

    bool isIntersect(Segment sg) {
        Point Q1 = sg.P1, Q2 = sg.P2;
        Vector P1Q1 = Q1 - P1;
        Vector P1Q2 = Q2 - P1;
        Vector P1P2 = P2 - P1;
        Vector Q1P1 = P1 - Q1;
        Vector Q1P2 = P2 - Q1;
        Vector Q1Q2 = Q2 - Q1;
        ll f1 = P1Q1 & P1P2;
        ll f2 = P1Q2 & P1P2;
        ll f3 = Q1P1 & Q1Q2;
        ll f4 = Q1P2 & Q1Q2;
        bool ok1 = (f1 == 0 || f2 == 0 || (min(f1, f2) < 0 && max(f1, f2) > 0));
        bool ok2 = (f3 == 0 || f4 == 0 || (min(f3, f4) < 0 && max(f3, f4) > 0));
        if (ok1 && ok2) {
            return true;
        }
        return false;
    }

    bool pointOn(Point P) {
        if (((P - P1) & (P2 - P1)) == 0 &&
            min(P1.x, P2.x) <= P.x && P.x <= max(P1.x, P2.x) &&
            min(P1.y, P2.y) <= P.y && P.y <= max(P1.y, P2.y)) {
            return true;
        }
        return false;
    }
};

struct Poly {
    int n;
    vector<Point> pts;

    Poly() {}
    Poly(int n) : n(n) {
        pts.resize(n);
    }

    void in() {
        for (int i = 0; i < n; i++) {
            pts[i].in();
        }
    }

    bool pointIn(Point P) {
        Segment ray(P, Point(X, Y));
        bool in = false;
        for (int i = 0; i < n; i++) {
            int j = (i + 1) % n;
            Segment sg = Segment(pts[i], pts[j]);
            if (sg.pointOn(P)) return true;
            in ^= ray.isIntersect(sg);
        }
        return in;
    }
};

int main() {
    freopen("point.in", "r", stdin);
    freopen("point.out", "w", stdout);

    int n;
    scanf("%d", &n);

    Point P;
    P.in();

    Poly poly(n);
    poly.in();

    puts(poly.pointIn(P) ? "YES" : "NO");
}
