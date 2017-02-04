#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

using ll = long long;

int n, L;
void f(vector<int>& a) {
    for (int i = int(a.size()) - 1; i >= 0; --i) {
        a[i] -= a[0];
        if (a[i] < 0) a[i] += L;
    }
}

int main() {
#if __APPLE__
    freopen("B.in", "r", stdin);
    freopen("B.out", "w", stdout);
#endif

    cin >> n >> L;

    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    vector<int> b(n);
    for (int i = 0; i < n; ++i) {
        cin >> b[i];
    }

    f(a);
    f(b);

    for (int i = 0; i < n + 1; ++i) {
        if (a == b) {
            cout << "YES" << endl;
            return 0;
        }
        rotate(a.begin(), a.begin() + 1, a.end());
        f(a);
    }
    cout << "NO" << endl;
}
