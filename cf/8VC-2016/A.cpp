#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

int main() {
    int n;
    scanf("%d", &n);

    vector<int> a, b;
    int st1 = -1, st2 = -1;
    for (int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);
        if (x != 0) {
            if (x == 1) st1 = a.size();
            a.push_back(x);
        }
    }
    for (int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);
        if (x != 0) {
            if (x == 1) st2 = b.size();
            b.push_back(x);
        }
    }

    rotate(a.begin(), a.begin() + st1, a.end());
    rotate(b.begin(), b.begin() + st2, b.end());

    for (int i = 0; i < (int)a.size(); i++) {
        if (a[i] != b[i]) {
            puts("NO");
            return 0;
        }
    }
    puts("YES");
}
