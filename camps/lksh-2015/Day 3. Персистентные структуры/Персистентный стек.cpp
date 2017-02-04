#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct Node {
    Node *prev;
    ll sum;

    Node() : prev(nullptr), sum(0) {}
};

int main() {
#if __APPLE__
    freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
#else
    freopen("snowmen.in", "r", stdin);
    freopen("snowmen.out", "w", stdout);
#endif

    int n;
    scanf("%d", &n);

    vector<Node*> stacks(n + 1);
    stacks[0] = new Node();
    for (int i = 1; i <= n; i++) {
        int t;
        ll m;
        scanf("%d%lld", &t, &m);

        if (m == 0) {
            stacks[i] = stacks[t]->prev;
        } else {
            stacks[i] = new Node();
            stacks[i]->prev = stacks[t];
            stacks[i]->sum = stacks[t]->sum + m;
        }
    }

    ll ans = 0;
    for (int i = 0; i <= n; i++) {
        ans += stacks[i]->sum;
    }
    printf("%lld\n", ans);
}
