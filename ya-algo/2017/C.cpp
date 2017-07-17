#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

int main() {
#if __APPLE__
    //freopen("C.in", "r", stdin);
    //freopen("C.out", "w", stdout);
#endif

    int n;
    scanf("%d", &n);

    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &a[i]);
    }

    int lb = -1, rb = n;
    while (lb + 1 < rb) {
        int k = (lb + rb) / 2;
        map<vector<int>, int> mp;
        bool ok = true;
        for (int i = k; i < n; ++i) {
            vector<int> prev;
            for (int j = i - 1; j >= i - k; --j) {
                prev.push_back(a[j]);
            }
            auto it = mp.find(prev);
            if (it != mp.end() && it->se != a[i]) {
                ok = false;
                break;
            }
            mp[prev] = a[i];
        }

        if (ok) {
            rb = k;
        } else {
            lb = k;
        }
    }

    printf("%d\n", rb);
}
