#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <climits>
#include <algorithm>
#define ll long long
using namespace std;

struct Point {
    ll x, y;
    Point() {};
    Point(ll _x, ll _y):x(_x), y(_y) {}
};

bool cmp_x(Point a, Point b) {
    return a.x < b.x;
}

bool cmp_y(Point a, Point b) {
    return a.y < b.y;
}

ll dist(Point a, Point b) {
    return max(abs(a.x-b.x), abs(a.y-b.y));
}

Point FindNearest(ll x, ll y, vector<Point> p_x, vector<Point> p_y) {
    Point res;
    ll max = LLONG_MAX;
    for (ll i = 0; i < p_x.size(); i++) {
        if (dist(Point(x, y), p_x[i]) < max) {
            max = dist(Point(x, y), p_x[i]);
            res.x = p_x[i].x;
            res.y = p_x[i].y;
        }
    }
    return res;
}

int main() {
    freopen("points.in", "r", stdin);
    freopen("points.out", "w", stdout);
    
    ll n, q;
    cin >> n >> q;
    
    ll m;
    cin >> m;
    
    ll a, b, c;
    cin >> a >> b >> c;
    
    ll d, e, f;
    cin >> d >> e >> f;
    
    vector<Point> p_x(n), p_y(n);
    for (ll i = 0; i < p_x.size(); i++) {
        cin >> p_x[i].x >> p_x[i].y;
        p_y[i].x = p_x[i].x;
        p_y[i].y = p_x[i].y;
    }
    sort(p_x.begin(), p_x.end(), cmp_x);
    // sort(p_y.begin(), p_y.end(), cmp_y);
    ll qx, qy;
    cin >> qx >> qy;

    ll ans = 0;
    for (ll i = 0; i < q; i++) {
        Point q = FindNearest(qx, qy, p_x, p_y);
        ll dst = dist(q, Point(qx, qy));
        ans += dst;
        qx = (abs(a*qx + b*dst + c) % (2*m + 1)) - m;
        qy = (abs(d*qy + e*dst + f) % (2*m + 1)) - m;
    }
    cout << ans;
}