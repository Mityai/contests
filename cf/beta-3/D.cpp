#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 5e4;

void no() {
    puts("-1");
    exit(0);
}

int main() {
    char s[N + 2];
    scanf("%s", s);

    int n = strlen(s);
    set<pair<int, int>> q;
    ll ans = 0;
    int bal = 0;
    for (int i = 0; i < n; ++i) {
        if (s[i] == '(') {
            ++bal;
        } else if (s[i] == ')') {
            --bal;
        } else if (s[i] == '?') {
            int a, b;
            scanf("%d%d", &a, &b);
            ans += b;
            q.insert({a - b, i});
            s[i] = ')';
            --bal;
        }
        if (bal < 0) {
            if (q.empty()) no();
            auto v = *q.begin();
            q.erase(q.begin());
            bal += 2;
            s[v.second] = '(';
            ans += v.first;
        }
    }

    if (bal != 0) no();

    printf("%lld\n", ans);
    printf("%s\n", s);
}
