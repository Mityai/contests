#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

using ll = long long;

int main() {
#if __APPLE__
    freopen("A.in", "r", stdin);
    freopen("A.out", "w", stdout);
#endif

    ios_base::sync_with_stdio(false);

    string s1, s2;
    cin >> s1 >> s2;

    int n;
    cin >> n;

    cout << s1 << ' ' << s2 << '\n';
    for (int i = 0; i < n; ++i) {
        string from, to;
        cin >> from >> to;
        if (s1 == from) s1 = to;
        else s2 = to;
        cout << s1 << ' ' << s2 << '\n';
    }
}
