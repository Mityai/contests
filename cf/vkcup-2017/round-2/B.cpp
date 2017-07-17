#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <string>
#include <cmath>
#define X first
#define Y second
 
using namespace std;
 
typedef long long ll;
 
const ll dd = 1e6;
const ll inf = 1e9 + 7;
 
const double eps = 1e-8;

typedef pair<double, double> Point;

double sqr(double x) {
    return x * x;
}

int main() {
#ifdef _DEBUG
    freopen("B.in", "r", stdin);
    freopen("B.out", "w", stdout);
#endif

    int n;
    scanf("%d", &n);

    vector<Point> pts(n);
    for (int i = 0; i < n; ++i) {
        scanf("%lf%lf", &pts[i].X, &pts[i].Y);
    }

    double ans = 1e18;

    for (int i = 0; i < n; ++i) {
        int prev = (i - 1 + n) % n;
        int next = (i + 1) % n;
        double a = pts[prev].Y - pts[next].Y;
        double b = pts[next].X - pts[prev].X;
        double c = -a * pts[prev].X - b * pts[prev].Y;
        double z = sqrt(a * a + b * b);
        a /= z;
        b /= z;
        c /= z;
        double dist = fabs(a * pts[i].X + b * pts[i].Y + c);
        ans = min(ans, dist / 2);
        ans = min(ans, sqrt(sqr(pts[i].X - pts[next].X) + sqr(pts[i].Y - pts[next].Y)) / 2);
    }

    printf("%.10lf\n", ans);
}
