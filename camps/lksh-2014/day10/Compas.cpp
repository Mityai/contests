#include <iostream>
#include <cstdio>
#include <climits>
#include <cstdlib>
#include <cmath>

#define sqr(x) x * x

typedef long long ll;

using namespace std;

struct Point {
    int x, y;

    void input() {
        scanf("%d%d", &x, &y);
    }

    bool operator == (const Point &pt) {
        return x == pt.x && y == pt.y;
    }
};

struct Vect {
    int x, y;

    void input() {
        scanf("%d%d", &x, &y);
    }

    Vect() {};
    Vect(Point pt1, Point pt2) {
        x = pt2.x - pt1.x;
        y = pt2.y - pt1.y;
    }
};

int operator & (Vect vc1, Vect vc2) {
    return vc1.x * vc2.y - vc1.y * vc2.x;
}

int operator * (Vect vc1, Vect vc2) {
    return vc1.x * vc2.x + vc1.y * vc2.y;
}

int main() {
    freopen("treasure.in", "r", stdin);
    freopen("treasure.out", "w", stdout);

    Point A, B;
    Vect C;
    
    A.input();
    B.input();
    C.input();

    Vect AB = Vect(A, B);

    if (A == B) {
        printf("X\n");
    } else {
        if ((AB & C) == 0 && (AB * C) > 0) {
            printf("N\n");
        } else if ((AB & C) > 0 && (AB * C) > 0) {
            printf("NE\n");
        } else if ((AB & C) > 0 && (AB * C) == 0) {
            printf("E\n");
        } else if ((AB & C) > 0 && (AB * C) < 0) {
            printf("SE\n");
        } else if ((AB & C) == 0 && (AB * C) < 0) {
            printf("S\n");
        } else if ((AB & C) < 0 && (AB * C) < 0) {
            printf("SW\n");
        } else if ((AB & C) < 0 && (AB * C) == 0) {
            printf("W\n");
        } else if ((AB & C) < 0 && (AB * C) > 0) {
            printf("NW\n");
        }
    }
}