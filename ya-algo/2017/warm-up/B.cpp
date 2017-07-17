#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

int main() {
#if __APPLE__
#endif

    vector<pair<int, int>> a(4);
    for (int i = 0; i < a.size(); ++i) {
        scanf("%d", &a[i].se);
        a[i].fi = i;
    }

    do {
        int x = a[0].se + a[1].se;
        int y = a[2].se + a[3].se;
        if (x == y) {
            puts("Yes");
            return 0;
        }
    } while (next_permutation(a.begin(), a.end()));
    puts("No");
}
