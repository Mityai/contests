#include <bits/stdc++.h>
using namespace std;

void no() {
    puts("-1");
    exit(0);
}

struct S {
    int d, c, i;
};

bool operator<(const S& a, const S& b) {
    return a.d < b.d;
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);

    vector<vector<S>> st(n + 1);
    vector<int> ex(n + 1, -1);
    for (int i = 0; i < m; ++i) {
        int s, d, c;
        scanf("%d%d%d", &s, &d, &c);
        st[s].push_back(S{d, c, i});
        ex[d] = i;
    }

    vector<int> dd(n + 1);
    vector<char> ready(m);
    set<S> q;
    for (int i = 1; i <= n; ++i) {
        for (auto& v : st[i]) {
            q.insert(v);
        }
        if (ex[i] != -1) {
            if (!ready[ex[i]]) {
                no();
            }
            dd[i] = m + 1;
        } else {
            if (!q.empty()) {
                auto it = *q.begin();
                q.erase(q.begin());
                --it.c;
                dd[i] = it.i + 1;
                if (it.c != 0) {
                    q.insert(it);
                } else {
                    ready[it.i] = true;
                }
            }
        }
    }

    for (int i = 1; i <= n; ++i) {
        printf("%d ", dd[i]);
    }
    putchar('\n');
}
