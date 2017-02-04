#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <cmath>
#define ll long long
#define eps 5e-7;
using namespace std;
 
double max_(double a, double b) {
    if (a > b) {
        return a;
    }
    return b;
}
 
double min_(double a, double b) {
    if (a < b) {
        return a;
    }
    return b;
}
 
struct Poll {
    ll x, y;
    void input() {
        cin >> x >> y;
    }
};
 
struct Segment {
    Poll p1;
    Poll p2;
     
    ll a, b, c;
     
    void input() {
        p1.input();
        p2.input();
        if (p1.x > p2.x) {
            swap(p1, p2);
        }
    }
     
    void CreateSeg() {
        a = p2.y - p1.y;
        b = p1.x - p2.x;
        c = -a * p1.x - b * p1.y;
    }
};
 
ll vec_pr(Poll a, Poll p, Poll b) {
    ll k = (b.x - p.x) * (a.y - p.y) - (a.x - p.x) * (b.y - p.y);
    if (k > 0) {
        return 1;
    } else if (k < 0) {
        return -1;
    }
    return 0;
}
 
bool inter2(Poll p, Poll p1, Poll p2) {
    return  min(p1.x, p2.x) <= p.x && p.x <= max(p1.x, p2.x) &&
            min(p1.y, p2.y) <= p.y && p.y <= max(p1.y, p2.y);
}

bool LineIn(Segment A, Segment B) {
    if (A.a * B.p1.x + A.b * B.p1.y + A.c == 0 &&
        A.a * B.p2.x + A.b * B.p2.y + A.c == 0) {
        return true;
    }
    return false;
}
 
bool inter(Segment a, Segment b) {
    if (LineIn(a, b)) {
        if (inter2(a.p1, b.p1, b.p2) || inter2(a.p2, b.p1, b.p2) || inter2(b.p1, a.p1, a.p2) || inter2(b.p2, a.p1, a.p2)) {
            return false;
        }
    }
    if (vec_pr(a.p1, a.p2, b.p1) != vec_pr(a.p1, a.p2, b.p2) && 
        vec_pr(b.p1, b.p2, a.p1) != vec_pr(b.p1, b.p2, a.p2)) {
        return false;
    }
    return true;
}
 
double getA(ll a, ll b, ll c, ll d) {
    return double(a * d - b * c);
}
 
int main() {
    freopen("segments.in", "r", stdin);
    freopen("segments.out", "w", stdout);

    Segment A, B;
    A.input();
    B.input();
    A.CreateSeg();
    B.CreateSeg();
    if (inter(A, B)) {
        cout << "Empty";
    } else {
        if (LineIn(A, B) &&
            (inter2(A.p1, B.p1, B.p2) || inter2(A.p2, B.p1, B.p2) || inter2(B.p1, A.p1, A.p2) || inter2(B.p2, A.p1, A.p2))) {
            double x_1 = A.p1.x, x_2 = A.p2.x, x_3 = B.p1.x, x_4 = B.p2.x;
            double y_1 = A.p1.y, y_2 = A.p2.y, y_3 = B.p1.y, y_4 = B.p2.y;
            if (x_1 > x_2)
                swap(x_1, x_2);
            if (x_3 > x_4)
                swap(x_3, x_4);
            double ans_x1 = max_(x_1, x_3);
            double ans_x2 = min_(x_2, x_4);
            if (ans_x1 > ans_x2) {
                swap(ans_x1, ans_x2);
            }
 
            if (y_1 > y_2)
                swap(y_1, y_2);
            if (y_3 > y_4)
                swap(y_3, y_4);
            double ans_y1 = max_(y_1, y_3);
            double ans_y2 = min_(y_2, y_4);
            if (ans_x1 == ans_x2 && ans_y1 > ans_y2) {
                swap(ans_y1, ans_y2);
            } else if (A.a < 0 && ans_x1 != ans_x2) {
                if (ans_y1 < ans_y2) {
                    swap(ans_y1, ans_y2);
                }
            }
            if (ans_x1 == ans_x2 && ans_y1 == ans_y2) {
                printf("%.10lf %.10lf", ans_x1, ans_y1);
            } else {
                printf("%.10lf %.10lf\n", ans_x1, ans_y1);
                printf("%.10lf %.10lf", ans_x2, ans_y2);
            }
        } else {
            double x = fabs(getA(-A.c, A.b, -B.c, B.b)) / fabs(getA(A.a, A.b, B.a, B.b));
            double y = fabs(getA(A.a, -A.c, B.a, -B.c)) / fabs(getA(A.a, A.b, B.a, B.b));
            printf("%.10lf %.10lf\n", x, y);
        }
    }
}