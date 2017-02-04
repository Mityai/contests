#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

using ll = long long;

int main() {
    int n, m;
    scanf("%d%d", &n, &m);

    vector<string> a, b;
    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        a.push_back(s);
    }
    for (int i = 0; i < m; ++i) {
        string s;
        cin >> s;
        b.push_back(s);
    }

    int com = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (a[i] == b[j]) {
                ++com;
                break;
            }
        }
    }

    int words1 = n - com + (com + 1) / 2;
    int words2 = m - com + com / 2;

    if (words1 > words2) {
        puts("YES");
    } else {
        puts("NO");
    }
}
