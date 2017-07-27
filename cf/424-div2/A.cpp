#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    scanf("%d", &n);

    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &a[i]);
    }

    for (int i = 0; i < n; ++i) {
        for (int j = i; j < n; ++j) {
            bool ok = true;
            for (int k = 0; k < i; ++k) {
                if (a[k] >= a[k + 1]) ok = false;
            }
            for (int k = j + 1; k < n; ++k) {
                if (a[k - 1] <= a[k]) ok = false;
            }
            for (int k = i; k <= j; ++k) {
                if (a[k] != a[i]) ok = false;
            }
            if (ok) return puts("YES"), 0;
        }
    }
    puts("NO");
}
