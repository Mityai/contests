//#include <bits/stdc++.h>
#include <cstdio>
#include <string>
#include <iostream>
using namespace std;

typedef long long ll;

ll N, X, Y;

bool ask(ll x, ll y) {
    if (x < 1 || y < 1 || x > N || y > N) return false;
    printf("examine %lld %lld\n", x, y);
    fflush(stdout);
    string s;
    cin >> s;
    return s == "true";
}

int main() {
    scanf("%lld%lld%lld", &N, &X, &Y);

    ll d = 1;
    while (ask(X + d, Y)) {
        d *= 2;
    }
    
    ll rightX;
    {
        ll lb = X, rb = X + d;
        while (lb + 1 < rb) {
            ll mb = (lb + rb) / 2;
            if (ask(mb, Y)) lb = mb;
            else rb = mb;
        }
        rightX = lb;
    }

    d = 1;
    while (ask(X - d, Y)) {
        d *= 2;
    }

    ll leftX;
    {
        ll lb = X - d, rb = X;
        while (lb + 1 < rb) {
            ll mb = (lb + rb) / 2;
            if (!ask(mb, Y)) lb = mb;
            else rb = mb;
        }
        leftX = rb;
    }

    ll m = rightX - leftX + 1;

    X = leftX;

    d = 1;
    while (ask(X, Y - d)) {
        d *= 2;
    }

    ll downY;
    {
        ll lb = Y - d, rb = Y;
        while (lb + 1 < rb) {
            ll mb = (lb + rb) / 2;
            if (!ask(X, mb)) lb = mb;
            else rb = mb;
        }
        downY = rb;
    }

    Y = downY;

    while (ask(X - 2 * m, Y)) {
        X -= 2 * m;
    }

    while (ask(X, Y - 2 * m)) {
        Y -= 2 * m;
    }

    while (ask(X - m, Y - m)) {
        X -= m;
        Y -= m;
    }

    X += m + m + m / 2;
    Y += m + m + m / 2;

    printf("solution %lld %lld\n", X, Y);
}
