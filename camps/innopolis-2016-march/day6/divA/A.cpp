#include <bits/stdc++.h>
#define left hladfs
#define right ljkads
using namespace std;

typedef long long ll;

map<ll, ll> left, right;

void ask(ll v) {
    if (left[v] != 0) return;
    cout << v << endl;
    cin >> left[v] >> right[v];
    if (left[v] == 0) left[v]--;
    if (right[v] == 0) right[v]--;
}

void ans(ll ret) {
    cout << -ret << endl;
    exit(0);
}

int H = 0;

bool has(ll k) {
    ll v = 1;
    for (int h = 0; h < H; h++) {
        ask(v);
        if (k & 1) {
            v = right[v];
        } else {
            v = left[v];
        }
        k /= 2;
    }
    ask(v);
    if (k == 0 && left[v] != -1) return true;
    if (k == 1 && right[v] != -1) return true;
    return false;
}

int main() {
    int v = 1;
    while (true) {
        ask(v);
        if (right[v] == -1) break;
        H++;
        v = right[v];
    }

    int maxH = 0;
    v = 1;
    while (true) {
        ask(v);
        if (left[v] == -1) break;
        maxH++;
        v = left[v];
    }

    if (H == maxH) {
        ans((1LL << (H + 1)) - 1);
    }

    ll lb = 1, rb = (1LL << maxH) + 1;
    while (lb + 1 < rb) {
        ll mb = (lb + rb) / 2;

        if (has(mb - 1)) lb = mb;
        else rb = mb;
    }

    ans((1LL << (H + 1)) - 1 + lb);
}
