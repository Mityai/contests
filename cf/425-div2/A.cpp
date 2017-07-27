#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#if __APPLE__
#define eprintf(...) fprintf(stderr, __VA_ARGS__)
#else
#define eprintf(...)
#endif

int main() {
    ll n, k;
    scanf("%lld%lld", &n, &k);

    ll full_steps = n / k;
    if (full_steps % 2 == 1) {
        puts("YES");
    } else {
        puts("NO");
    }
}
