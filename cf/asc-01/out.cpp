#include <bits/stdc++.h>
#define Vector Point
using namespace std;

const double eps = 1e-6;
const double pi = acos(-1);

double sqr(double x) {
    return x * x;
}

struct Point {
    double x, y;

    void scan() {
        scanf("%lf%lf", &x, &y);
    }
};

Vector operator - (const Vector& vc1, const Vector& vc2) {
    return Vector({vc1.x - vc2.x, vc1.y - vc2.y});
}

double dist(const Point& pt1, const Point& pt2) {
    return sqrt(sqr(pt1.x - pt2.x) + sqr(pt1.y - pt2.y));
}

struct Circle {
    Point O;
    double r;

    void scan() {
        O.scan();
        scanf("%lf", &r);
    }
};

bool is_intersect(const Circle& c1, const Circle& c2) {
    return dist(c1.O, c2.O) < c1.r + c2.r - eps;
}

double operator & (const Vector& vc1, const Vector& vc2) {
    return vc1.x * vc2.y - vc1.y * vc2.x;
}

double operator * (const Vector& vc1, const Vector& vc2) {
    return vc1.x * vc2.x + vc1.y * vc2.y;
}

double get_angle(const Vector& vc1, const Vector& vc2) {
    return atan2(vc1 & vc2, vc1 * vc2);
}

vector<Circle> a;
vector<vector<int>> g;
vector<char> used;
vector<double> was;
Point P;

void dfs(int v, double cur_angle) {
    used[v] = true;
    was[v] = cur_angle;
    for (int u : g[v]) {
        if (used[u]) {
            if (fabs(cur_angle + get_angle(a[v].O - P, a[u].O - P) - was[u]) > 2 * pi - eps) {
                puts("NO");
                exit(0);
            }
        } else {
            dfs(u, cur_angle + get_angle(a[v].O - P, a[u].O - P));
        }
    }
}

int main() {
    freopen("out.in", "r", stdin);
    freopen("out.out", "w", stdout);

    int n;
    scanf("%d", &n);

    a.resize(n);
    for (int i = 0; i < n; ++i) {
        a[i].scan();
    }

    Circle man;
    man.scan();

    for (int i = 0; i < n; ++i) {
        a[i].r += man.r;
    }

    P = man.O;

    g.resize(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            if (is_intersect(a[i], a[j])) {
                g[i].push_back(j);
                g[j].push_back(i);
            }
        }
    }
    
    used.resize(n, false);
    was.resize(n);
    for (int i = 0; i < n; ++i) {
        if (!used[i]) {
            dfs(i, 0);
        }
    }
    puts("YES");
}
