#include <bits/stdc++.h>
using namespace std;

bool ok(int n, const vector<char>& good) {
    vector<int> digs;
    if (n == 0) digs.push_back(0);
    while (n > 0) {
        digs.push_back(n % 10);
        n /= 10;
    }
    for (int x : digs) {
        if (!good[x]) return false;
    }
    return true;
}

int main() {
    int n, k;
    scanf("%d%d", &n, &k);

    vector<char> good(10, true);
    for (int i = 0; i < k; ++i) {
        int x;
        scanf("%d", &x);
        good[x] = false;
    }

    while (!ok(n, good)) {
        ++n;
    }
    printf("%d\n", n);
}
