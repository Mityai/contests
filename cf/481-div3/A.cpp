#include <bits/stdc++.h>
using namespace std;

#if __APPLE__
#define eprintf(...) fprintf(stderr, __VA_ARGS__)
#else
#define eprintf(...)
#endif

int main() {
#if __APPLE__
    freopen(".in", "r", stdin);
    freopen(".out", "w", stdout);
#endif

    int n;
    scanf("%d", &n);

    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &a[i]);
    }

    vector<char> was(1001);
    vector<int> ans;
    for (int i = n - 1; i >= 0; --i) {
        if (!was[a[i]]) {
            ans.push_back(a[i]);
        }
        was[a[i]] = true;
    }

    printf("%d\n", (int)ans.size());
    for (int i = (int)ans.size() - 1; i >= 0; --i) {
        printf("%d ", ans[i]);
    }
}
