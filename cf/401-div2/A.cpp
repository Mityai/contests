#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

using ll = long long;

int main() {
    int n;
    scanf("%d", &n);

    int x;
    scanf("%d", &x);

    n %= 6;

    vector<int> a = {0, 1, 2};
    for (int i = 0; i < n; ++i) {
        if (i % 2 == 0) {
            swap(a[0], a[1]);
        } else {
            swap(a[1], a[2]);
        }
    }

    printf("%d\n", a[x]);
}
