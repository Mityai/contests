#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

template<typename T>
class Rational {
public:
    Rational(const T& a = 0, const T& b = 1) : n(a), m(b) {
        reduce();
    }

    Rational& operator += (const Rational& oth) {
        n = n * oth.m + oth.n * m;
        m *= oth.m;
        reduce();
        return *this;
    }

    Rational& operator -= (const Rational& oth) {
        n = n * oth.m - oth.n * m;
        m *= oth.m;
        reduce();
        return *this;
    }

    Rational& operator *= (const Rational& oth) {
        n *= oth.n;
        m *= oth.m;
        reduce();
        return *this;
    }

    Rational& operator /= (const Rational& oth) {
        n *= oth.m;
        m *= oth.n;
        reduce();
        return *this;
    }

    Rational operator + (const Rational& b) const {
        auto tmp = *this;
        tmp += b;
        return tmp;
    }

    Rational operator - (const Rational& b) const {
        auto tmp = *this;
        tmp -= b;
        return tmp;
    }

    Rational operator * (const Rational& b) const {
        auto tmp = *this;
        tmp *= b;
        return tmp;
    }

    Rational operator / (const Rational& b) const {
        auto tmp = *this;
        tmp /= b;
        return tmp;
    }

    bool operator < (const Rational& b) const {
        return n * b.m < b.n * m;
    }

    bool operator > (const Rational& b) const {
        return b < *this;
    }

    bool operator == (const Rational& b) const {
        return n == b.n && m == b.m;
    }

    bool operator != (const Rational& b) const {
        return !(*this == b);
    }

    bool operator <= (const Rational& b) const {
        return *this < b || *this == b;
    }

    bool operator >= (const Rational& b) const {
        return *this > b || *this == b;
    }

    double get_double() {
        return n * 1.0 / m;
    }

    T n, m;

private:

    T mabs(const T& x) {
        if (x < 0) {
            return -x;
        }
        return x;
    }

    void reduce() {
        if (m < 0) {
            m = -m;
            n = -n;
        }
        T g = gcd(mabs(n), m);
        n /= g;
        m /= g;
    }

    T gcd(T f, T h) {
        while (h != 0) {
            f %= h;
            std::swap(f, h);
        }
        return f;
    }
};

void no() {
    puts("-1");
    exit(0);
}

int main() {
#if __APPLE__
    freopen("C.in", "r", stdin);
    freopen("C.out", "w", stdout);
#endif

    int n;
    scanf("%d", &n);

    Rational<ll> x1, y1, x2, y2;
    scanf("%lld%lld%lld%lld", &x1.n, &y1.n, &x2.n, &y2.n);

    Rational<ll> mint, maxt(ll(1e18));
    for (int i = 0; i < n; ++i) {
        Rational<ll> rx, ry, vx, vy;
        scanf("%lld%lld%lld%lld", &rx.n, &ry.n, &vx.n, &vy.n);

        vector<Rational<ll>> dist;

        if (vx != 0) {
            Rational<ll> t = (x1 - rx) / vx;
            if (t >= 0) {
                if (vy == 0 && (ry == y1 || ry == y2)) {
                    no();
                }
                Rational<ll> newy = ry + t * vy;
                if (y1 <= newy && newy <= y2) {
                    dist.push_back(t);
                }
            }
        }
        if (vx != 0) { // x2
            Rational<ll> t = (x2 - rx) / vx;
            if (t >= 0) {
                if (vy == 0 && (ry == y1 || ry == y2)) {
                    no();
                }
                Rational<ll> newy = ry + t * vy;
                if (y1 <= newy && newy <= y2) {
                    dist.push_back(t);
                }
            }
        }
        if (vy != 0) { // y1
            Rational<ll> t = (y1 - ry) / vy;
            if (t >= 0) {
                if (vx == 0 && (rx == x1 || rx == x2)) {
                    no();
                }
                Rational<ll> newx = rx + t * vx;
                if (x1 <= newx && newx <= x2) {
                    dist.push_back(t);
                }
            }
        }
        if (vy != 0) { // y2
            Rational<ll> t = (y2 - ry) / vy;
            if (t >= 0) {
                if (vx == 0 && (rx == x1 || rx == x2)) {
                    no();
                }
                Rational<ll> newx = rx + t * vx;
                if (x1 <= newx && newx <= x2) {
                    dist.push_back(t);
                }
            }
        }

        sort(dist.begin(), dist.end());

        Rational<ll> curmin, curmax;
        if (x1 < rx && rx < x2 && y1 < ry && ry < y2) {
            curmin = 0;
            if (dist.empty()) {
                curmax = 1e18;
            } else {
                curmax = dist[0];
            }
        } else if (dist.size() >= 2) {
            curmin = dist[0];
            curmax = dist.back();
        } else {
            no();
        }

        mint = max(mint, curmin);
        maxt = min(maxt, curmax);
    }

    if (maxt > mint) {
        printf("%.10lf\n", mint.get_double());
    } else {
        no();
    }
}
