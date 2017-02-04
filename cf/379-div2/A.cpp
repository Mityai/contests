#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

using ll = long long;

int main() {
#if __APPLE__
    //freopen(".in", "r", stdin);
    //freopen(".out", "w", stdout);
#endif

    int n;
    cin >> n;

    string s;
    cin >> s;

    int cnt = 0;
    for (char c : s) {
        if (c == 'A') cnt++;
    }

    if (cnt > n - cnt) {
        cout << "Anton" << endl;
    } else if (n - cnt > cnt) {
        cout << "Danik" << endl;
    } else {
        cout << "Friendship" << endl;
    }
}
