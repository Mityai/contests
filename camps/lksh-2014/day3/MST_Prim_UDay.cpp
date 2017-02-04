#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <set>
#include <cmath>

typedef long long ll;

using namespace std;

const double INF = 2e9;

struct Point {
    int x, y;
};

double sqr(double x) {
    return x * x;
}

double distance(Point p1, Point p2) {
    return sqrt(sqr(double(p1.x - p2.x)) + sqr(double(p1.y - p2.y)));
}

int main() {
    freopen("unionday.in", "r", stdin);
    freopen("unionday.out", "w", stdout);

    int n;
    scanf("%d", &n);

    vector<Point> pts(n);
    for (int i = 0; i < n; i++) {
        scanf("%d%d", &pts[i].x, &pts[i].y);
    }

    double ans = 0;

    vector<char> used(n, false);
    vector<double> dist(n, INF);
    dist[0] = 0;
    for (int i = 0; i < n; i++) {
        int v = -1;

        for (int j = 0; j < n; j++) {
            if (!used[j] && (v == -1 || dist[v] > dist[j])) {
                v = j;
            }
        }

        ans += dist[v];

        used[v] = true;

        for (int j = 0; j < n; j++) {
            dist[j] = min(dist[j], distance(pts[v], pts[j]));
        }
    }

    printf("%.4lf\n", ans);
}