#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 1e5 + 123;

bool used[N];
int n, t, k;
int taken, all;
set<int> q;

int place(int len) {
    int cnt = len / (k + 1);
    if (cnt * (k + 1) + k <= len) cnt++;
    return cnt;
}

int cnt1(int i) {
    used[i] = true;
    int ret = 0;
    for (int i = 1; i <= n; i++) {
        if (!used[i] && used[i + 1]) {
            int len = 0;
            for (int j = i; j >= 1; j--) {
                if (!used[j]) {
                    len++;
                } else break;
            }
            int cnt = len / (k + 1);
            if (cnt * (k + 1) + k <= len) cnt++;
            ret += cnt;
        }
    }
    used[i] = false;
    return ret;
}

int cnt(int x) {
    int nxt = *q.upper_bound(x);
    int prv = *(--q.lower_bound(x));
    int len = nxt - prv - 1;
    int now = all - place(len);
    len = x - prv - 1;
    now += place(len);
    len = nxt - x - 1;
    now += place(len);
    return now;
}


int get(int len, int f) {
    int free = len - (f * (k + 1) - 1);
    int each = min(k, free);
    return (k - each) * f;
}

void recalc(int x) {
    int nxt = *q.upper_bound(x);
    int prv = *(--q.lower_bound(x));
    int len = nxt - prv - 1;
    int other = all - place(len);
    int here = max(0, t - other);
    taken -= get(len, here);
    all = cnt(x);

    len = x - prv - 1;
    other = all - place(len);
    here = max(0, t - other);
    taken += get(len, here);

    len = nxt - x - 1;
    other = all - place(len);
    here = max(0, t - other);
    taken += get(len, here);
}

void add(int x) {
    used[x] = true;
    q.insert(x);
    if (1 <= x && x <= n) {
        recalc(x);
    }
}

int main() {
    cin >> n >> t >> k;

    add(0), add(n + 1);

    all = place(n);
    taken = get(n, t);
    cout << taken << endl;

    int x;
    while (cin >> x) {
        if (cnt(x) >= t) {
            add(x);
            cout << 0 << ' ' << taken << endl;
        } else {
            cout << 1 << endl;
            break;
        }
    }
}
