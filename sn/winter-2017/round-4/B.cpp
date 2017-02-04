#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

using ll = long long;

int main() {
    int n, t;
    scanf("%d%d", &n, &t);

    vector<int> num(n + n, -1);
    map<string, int> was;
    vector<int> count(n);
    int del = 0;
    int unknown = n;
    int cnt = 0;
    for (int i = 0; i < t; ++i) {
        int p1, p2;
        string s1, s2;
        cin >> p1 >> p2;
        cin >> s1 >> s2;

        if (was.find(s1) == was.end()) {
            was[s1] = ++cnt;
        }
        if (was.find(s2) == was.end()) {
            was[s2] = ++cnt;
        }

        if (num[p1] == -1) {
            --unknown;
            ++count[was[s1]];
        }
        num[p1] = was[s1];
        if (num[p2] == -1) {
            --unknown;
            ++count[was[s2]];
        }
        num[p2] = was[s2];

        if (s1 == s2) {
            count[num[p1]] -= 2;
            ++del;
        }
    }

    int ans = 0;
    if (unknown <= 2) {
        ans = n / 2 - del;
    } else if (was.size() == n / 2) {
        ans = n / 2 - del;
    } else {
        for (int i = 0; i < n; ++i) {
            ans += (count[i] == 2);
        }
    }

    cout << ans << endl;
}
