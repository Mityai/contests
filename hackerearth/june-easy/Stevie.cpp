#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

#if __APPLE__
#define eprintf(...) fprintf(stderr, __VA_ARGS__)
#else
#define eprintf(...)
#endif

int main() {
    int n;
    scanf("%d", &n);

    vector<int> a(n), b(n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &a[i]);
    }
    map<int, int> mx;
    for (int i = 0; i < n; ++i) {
        scanf("%d", &b[i]);
        mx[a[i]] = max(mx[a[i]], b[i]);
    }

    for (int i = 0; i < n; ++i) {
        printf("%d ", mx[a[i]]);
    }
    puts("");
}
