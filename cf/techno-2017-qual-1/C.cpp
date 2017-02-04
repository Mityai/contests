#include <bits/stdc++.h>
#define fi first
#define se secodn
using namespace std;

using ll = long long;

int ask(int i, int j) {
    cout << "? " << i << ' ' << j << endl;
    int ret;
    cin >> ret;
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);

    int n;
    cin >> n;

    int a[n + 1];
    memset(a, 0, sizeof a);

    int a12 = ask(1, 2);
    int a13 = ask(1, 3);
    int a23 = ask(2, 3);

    a[2] = (a12 + a23 - a13) / 2;
    a[1] = a12 - a[2];
    a[3] = a23 - a[2];
    for (int i = 4; i <= n; i++) {
        a[i] = ask(1, i) - a[1];
    }

    cout << "! ";
    for (int i = 1; i <= n; i++) {
        cout << a[i] << ' ';
    }
    cout << endl;
}
