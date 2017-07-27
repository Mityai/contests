#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

#if __APPLE__
#define eprintf(...) fprintf(stderr, __VA_ARGS__)
#else
#define eprintf(...)
#endif

typedef long long ll;

const int N = 1e5;

int main() {
    int n;
    scanf("%d", &n);

    vector<char> used(N + 1);
    for (int i = 0; i < n; ++i) {
        int x;
        scanf("%d", &x);
        used[x] = true;
    }

    int ans = 0;
    for (int i = 0; i * 2 + 2 <= N; ++i) {
        ans += (used[i * 2 + 1] | used[i * 2 + 2]);
    }
    printf("%d\n", ans);
}
