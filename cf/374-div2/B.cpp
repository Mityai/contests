#include <bits/stdc++.h>

using namespace std;

using ll = long long;

int main() {
#if __APPLE__
    //freopen(".in", "r", stdin);
    //freopen(".out", "w", stdout);
#endif

    int n, k;
    cin >> n >> k;

    map<int, int> cnt;
    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        cnt[s.length()]++;
    }

    string pas;
    cin >> pas;

    int all = 0;
    for (int i = 0; i < pas.length(); ++i) {
        all += cnt[i];
    }

    int ans1 = all + (all / k) * 5 + 1;
    all += cnt[pas.length()];
    int ans2 = all;
    if (all % k == 0) {
        ans2 += (all / k - 1) * 5;
    } else {
        ans2 += (all / k) * 5;
    }
    cout << ans1 << ' ' << ans2 << endl;
}
