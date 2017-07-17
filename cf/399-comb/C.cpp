#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

using ll = long long;

const int N = 1e5;

int n, k, x;
vector<int> a;

void gostup() {
    for (int i = 0; i < k; ++i) {
        sort(a.begin(), a.end());
        cerr << a[0] << ' ' << a.back() << endl;
        for (int j = 0; j < n; j += 2) {
            a[j] ^= x;
        }
    }
    sort(a.begin(), a.end());
    cout << a.back() << ' ' << a[0] << endl;
}

int main() {
#if __APPLE__
    freopen("C.in", "r", stdin);
    //freopen("C.out", "w", stdout);
#endif

    scanf("%d%d%d", &n, &k, &x);

    a.resize(n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &a[i]);
    }

    gostup();
    return 0;

    sort(a.begin(), a.end());

    for (int i = 0; i < min(k, 10); ++i) {
        for (int j = 0; j < n; j += 2) {
            a[j] ^= x;
        }
        sort(a.begin(), a.end());
    }

    if (k > 10) {
        if (k % 2 == 1) {
            for (int j = 0; j < n; j += 2) {
                a[j] ^= x;
            }
            sort(a.begin(), a.end());
        }
    }
    printf("%d %d\n", a.back(), a[0]);
}
