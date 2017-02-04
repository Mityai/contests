#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

const int N = 1e5 + 123;
const int D = 10;
const int C = 10;

struct BigInt {
    vector<int> d;
    BigInt() {}
    BigInt(int x) {
        d.push_back(x);
    }
    BigInt(vector<int> &f) {
        d = f;
    }
    void out() {
        printf("%d", d.empty() ? 0 : d.back());
        for (int i = (int)d.size() - 2; i >= 0; i--) {
            printf("%d", d[i]);
        }
    }
};

inline void add(BigInt &A, BigInt &B) {
    auto &a = A.d;
    auto &b = B.d;
    for (int i = 0, carry = 0; i < (int)max(a.size(), b.size()) || carry; i++) {
        if (i == a.size()) a.push_back(0);
        if (i == b.size()) b.push_back(0);
        a[i] = a[i] + b[i] + carry;
        carry = (a[i] >= C);
        a[i] %= C;
    }
    while (a.size() >= 2 && a.back() == 0) a.pop_back();
}

inline void add(BigInt &A, const int &x) {
    auto &a = A.d;
    for (int i = 0, carry = x; i < (int)a.size() || carry; i++) {
        if (i == (int)a.size()) a.push_back(0);
        a[i] += carry;
        carry = (a[i] >= 10);
        if (carry) a[i] -= 10;
    }
}

inline void mult(BigInt &A, const int &x) {
    auto &a = A.d;
    for (int i = 0, carry = 0; i < (int)a.size() || carry; i++) {
        if (i == a.size()) a.push_back(0);
        ll cur = a[i] * 1LL * x + carry;
        a[i] = cur % C;
        carry = cur / C;
    }
    while (a.size() >= 2 && a.back() == 0) a.pop_back();
}

inline bool operator < (const BigInt &A, const BigInt &B) {
    auto a = A.d;
    auto b = B.d;
    if (a.size() < b.size()) return true;
    if (a.size() > b.size()) return false;
    for (int i = (int)a.size() - 1; i >= 0; i--) {
        if (a[i] < b[i]) return true;
        if (a[i] > b[i]) return false;
    }
    return false;
}

bool notfirst[D];

bool cmp(const pair<BigInt, int> &A, const pair<BigInt, int> &B) {
    auto &a = A.fi.d;
    auto &b = B.fi.d;
    if (a.size() > b.size()) return true;
    if (a.size() < b.size()) return false;
    for (int i = (int)a.size() - 1; i >= 0; i--) {
        if (a[i] > b[i]) return true;
        if (a[i] < b[i]) return false;
    }
    return false;
}

int main() {
    int n;
    scanf("%d", &n);

    vector<string> a(n);

    vector< pair<BigInt, int> > dig(D);

    for (int i = 0; i < D; i++) {
        dig[i].fi = BigInt(0);
        dig[i].fi.d.reserve(N);
        dig[i].se = i;
    }

    vector< vector<int> > x(N);
    for (int i = 0; i < n; i++) {
        char s[N];
        scanf(" %s", s);
        a[i] = string(s);
        if (a[i].length() > 1) {
            notfirst[a[i][0] - 'a'] = true;
        }
        for (int j = 0; j < (int)a[i].size(); j++) {
            x[N - j - 1].push_back(a[i][(int)a[i].size() - j - 1] - 'a');
        }
    }

    for (int i = 0; i < D; i++) {
        if (dig[i].fi.d.empty()) dig[i].fi.d.push_back(0);
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < D; j++) {
            if (dig[j].fi.d.size() >= 2 || dig[j].fi.d[0] != 0) {
                dig[j].fi.d.push_back(0);
            }
        }
        int sum[D];
        memset(sum, 0, sizeof sum);
        for (int y : x[i]) {
            sum[y]++;
        }
        for (int j = 0; j < D; j++) {
            if (sum[j] != 0) {
                reverse(dig[j].fi.d.begin(), dig[j].fi.d.end());
                add(dig[j].fi, sum[j]);
                reverse(dig[j].fi.d.begin(), dig[j].fi.d.end());
            }
        }
    }

    for (int i = 0; i < D; i++) {
        reverse(dig[i].fi.d.begin(), dig[i].fi.d.end());
    }

    for (int i = 0; i < D; i++) {
        while (dig[i].fi.d.size() >= 2 && dig[i].fi.d.back() == 0) dig[i].fi.d.pop_back();
    }

    sort(dig.begin(), dig.end(), cmp);

    int id = -1;
    for (int i = 0; i < D; i++) {
        if (!notfirst[dig[i].se] && (id == -1 || dig[i].fi < dig[id].fi)) {
            id = i;
        }
    }

    if (id != -1) {
        auto v = dig[id];
        dig.erase(dig.begin() + id);
        dig.push_back(v);
    }

    BigInt ans = BigInt(0);
    for (int i = 0; i < D; i++) {
        mult(dig[i].fi, D - i - 1);
        add(ans, dig[i].fi);
    }
    ans.out();
    puts("");
}
