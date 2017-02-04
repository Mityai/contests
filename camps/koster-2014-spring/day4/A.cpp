#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <cmath>
#define ll long long
using namespace std;
 
struct Point {
    double x, y;
    double n;
};
 
bool cmp(Point a, Point b) {
    if (a.x == b.x) {
        return a.y < b.y;
    }
    return a.x < b.x;
}
 
int vect(Point p, Point p1, Point p2) {
    double k = (p1.x - p.x) * (p2.y - p.y) - (p2.x - p.x) * (p1.y - p.y);
    if (k > 0) return 1;
    if (k < 0) return -1;
    return 0;
}
 
double get_area(Point p1, Point p2) {
    return 0.5*(p1.x * p2.y - p2.x * p1.y);
}
 
double dist(Point p1, Point p2) {
    return sqrt( (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y) );
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
 
    int n;
    scanf("%d", &n);
    vector<Point> p(n);
    for (int i = 0; i < n; i++) {
        scanf("%lf%lf", &p[i].x, &p[i].y);
        p[i].n = i+1;
    }
    
    sort(p.begin(), p.end(), cmp);

    Point A = p.front(), B = p.back();
    int aa = B.y - A.y;
    int bb = A.x - B.x;
    int cc = B.x * A.y - A.x * B.y;
    
    vector<Point> convex_up;
    convex_up.push_back(A);

    vector<Point> convex_down;
    convex_down.push_back(A);
    for (int i = 0; i < p.size(); i++) {
        if (p[i].x * aa + p[i].y * bb + cc < 0 || p[i].n == B.n) {
            if (convex_up.size() == 1) {
                convex_up.push_back(p[i]);
            } else {
                while (convex_up.size() > 1 && vect(convex_up[convex_up.size()-1], convex_up[convex_up.size()-2], p[i]) <= 0) {
                    convex_up.pop_back();
                }
                convex_up.push_back(p[i]);
            }
        }
        if (p[i].x * aa + p[i].y * bb + cc > 0 || p[i].n == B.n) {
            if (convex_down.size() == 1) {
                convex_down.push_back(p[i]);
            } else {
                while (convex_down.size() > 1 && vect(convex_down[convex_down.size()-1], convex_down[convex_down.size()-2], p[i]) >= 0) {
                    convex_down.pop_back();
                }
                convex_down.push_back(p[i]);
            }
        }
        if (convex_up.back().n == B.n && convex_down.back().n == B.n) {
            break;
        } 
    }
    convex_down.pop_back();
 
    double area = 0, perimetr = 0;
    // cout << convex_up.size() + convex_down.size() - 1 << endl;
    for (int i = 0; i < convex_down.size(); i++) {
        // cout << convex_down[i].n << ' ';
        if (i) {
            perimetr += dist(convex_down[i-1], convex_down[i]);
            area += get_area(convex_down[i-1], convex_down[i]);
        }
    }
    for (int i = convex_up.size() - 1; i > 0; i--) {
        // cout << convex_up[i].n << ' ';
        perimetr += dist(convex_up[i], convex_up[i-1]);
        area += get_area(convex_up[i], convex_up[i-1]);
        if (i == convex_up.size() - 1) {
            perimetr += dist(convex_down.back(), convex_up[i]);
            area += get_area(convex_down.back(), convex_up[i]);
        }
    }
    printf("%6lf", perimetr);
}