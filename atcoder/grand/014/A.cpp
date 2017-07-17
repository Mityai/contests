#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

int main() {
#if __APPLE__
    //freopen("A.in", "r", stdin);
    //freopen("A.out", "w", stdout);
#endif

    int A, B, C;
    cin >> A >> B >> C;

    int ans = 0;
    for (int i = 0; i < 1e7; ++i) {
        if (A % 2 == 1 || B % 2 == 1 || C % 2 == 1) {
            break;
        }
        int tmpA = A;
        int tmpB = B;
        int tmpC = C;
        A = (tmpB + tmpC) / 2;
        B = (tmpA + tmpC) / 2;
        C = (tmpA + tmpB) / 2;
        ++ans;
    }

    if (A % 2 == 0 && B % 2 == 0 && C % 2 == 0) {
        ans = -1;
    }
    printf("%d\n", ans);
}
