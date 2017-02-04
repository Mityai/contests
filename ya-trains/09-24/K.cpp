#include <bits/stdc++.h>

using namespace std;

bool ok(char c) {
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c == ' ');
}

const int N = 123456;
const int inf = 2e9;

int p[N], r[N];

int main() {
    string s;
    getline(cin, s);
    int n = s.size();
    int res = 0;
    for (int i = 0; i < n; i++) {
        p[i] = ok(s[i]);
        if (i > 0) p[i] += p[i - 1];
        res += (s[i] == '(') || (s[i] == ')');
    }
    int near = inf;
    for (int i = n - 1; i >= 0; i--) {
        if (s[i] == ')') near = i;
        r[i] = near;
    }
    for (int i = 0; i < n - 1; i++) {
        if (s[i] == '(' && r[i] < inf) {
            int sum = p[r[i]] - p[i];
            int len = r[i] - i - 1;
            if (len == sum) res -= 2;
        }
    }
    cout << res;
    return 0;
}
