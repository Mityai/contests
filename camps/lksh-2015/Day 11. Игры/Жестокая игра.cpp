#include <bits/stdc++.h>
using namespace std;

const int N = 5e3;

int d[N + 1];

void precalc() {
    d[0] = 0;

    for (int i = 2; i <= N; i++) {
        vector<int> A;
        for (int j = 1; j <= i; j++) {
            A.push_back(d[j - 1] ^ d[i - j]);
        }
        sort(A.begin(), A.end());
        A.erase(unique(A.begin(), A.end()), A.end());
        int j;
        for (j = 0; j < (int)A.size(); j++) {
            if (A[j] != j) break;
        }
        d[i] = j;
    }
}

int main() {
#if __APPLE__
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
#else
    freopen("cruel.in", "r", stdin);
    freopen("cruel.out", "w", stdout);
#endif

    precalc();

    int n;
    scanf("%d", &n);

    if (d[n]) {
        puts("Schtirlitz");
        for (int i = 1; i <= n; i++) {
            if (!(d[i - 1] ^ d[n - i])) {
                printf("%d\n", i);
            }
        }
    } else {
        puts("Mueller");
    }
}
