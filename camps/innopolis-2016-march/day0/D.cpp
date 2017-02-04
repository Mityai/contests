#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 123;

int f[N];

void setval(int pos, int val) {
    for (int i = pos; i < N; i = (i | (i + 1))) {
        f[i] = max(f[i], val);
    }
}

int getmax(int pos) {
    int ret = 0;
    for (int i = pos; i >= 0; i = (i & (i + 1)) - 1) { 
        ret = max(ret, f[i]);
    }
    return ret;
}

int main() {
    freopen("lock.in", "r", stdin);
    freopen("lock.out", "w", stdout);

    int n;
    scanf("%d", &n);

    int b[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", b + i);
    }

    for (int i = 0; i < n - 1; i++) {
        int mx = getmax(b[i]);
        setval(b[i], mx + 1);
    }

    printf("%d\n", n - (getmax(b[n - 1]) + 1));
}
