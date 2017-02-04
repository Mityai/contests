#include <bits/stdc++.h>
using namespace std;

const double INF = 1e18;

using ll = long long;

int n;
ll k;
vector<int> a;

pair<bool, double> check(double mb) {
    ll need = 0;
    vector<ll> here(n);
    for (int i = 0; i < n; ++i) {
        here[i] = ll(a[i] / mb);
        need += here[i];
    }

    ll rest = k - need;
    if (rest < 0) return {false, INF};
    vector<pair<double, int>> best(n);
    for (int i = 0; i < n; ++i) {
        double imp = INF;
        if (here[i] != 0) {
            imp = double(a[i]) / here[i] - double(a[i]) / (here[i] + 1);
        }
        best[i] = {imp, i};
    }
    sort(best.rbegin(), best.rend());
    
    for (int i = 0; i < min(rest, ll(n)); ++i) {
        ++here[best[i].second];
    }

    double tm = 0;
    for (int i = 0; i < n; ++i) {
        if (here[i] == 0) {
            return {false, INF};
        }
        tm += double(a[i]) / here[i];
    }

    return {true, tm};
}

int main() {
    freopen("tallbarn.in", "r", stdin);
    freopen("tallbarn.out", "w", stdout);

    scanf("%d%lld", &n, &k);

    a.resize(n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &a[i]);
    }

    double lb, rb = 1e15;
    for (int i = 0; i < n; ++i) {
        lb = max(lb, 1 / double(a[i]));
    }
    for (int it = 0; it < 100; ++it) {
        double mb = (lb + rb) / 2;

        if (check(mb).first) {
            rb = mb;
        } else {
            lb = mb;
        }
    }

    cout << (lb + rb) / 2 << endl;
    printf("%.10lf\n", check((lb + rb) / 2).second);
}
