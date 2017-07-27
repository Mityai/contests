#include <bits/stdc++.h>
#define rank asdalkssfahu
using namespace std;

const int N = 100;

int get_rank(vector<bitset<N>> a, int n, int m) {
    int rank = 0;
    for (int col = 0, row = 0; col < m && row < n; ++col) {
        for (int i = row; i < n; ++i) {
            if (a[i].test(col)) {
                swap(a[i], a[row]);
                break;
            }
        }
        if (!a[row].test(col)) continue;
        ++rank;
        for (int i = 0; i < n; ++i) {
            if (i != row && a[i].test(col)) {
                a[i] ^= a[row];
            }
        }
        ++row;
    }
    return rank;
}

bool is_prime(int x) {
    for (int i = 3; i * i <= x; i += 2) {
        if (x % i == 0) return false;
    }
    return true;
}

vector<int> get_primes(int t) {
    vector<int> primes(1, 2);
    for (int i = 3; primes.size() < t; i += 2) {
        if (is_prime(i)) primes.push_back(i);
    }
    return primes;
}

void mult2(vector<int>& a) {
    for (int i = 0, carry = 0; i < a.size() || carry; ++i) {
        if (i == a.size()) a.push_back(0);
        a[i] = a[i] * 2 + carry;
        carry = a[i] / 10;
        a[i] %= 10;
    }
    while (a.size() >= 2 && a.back() == 0) a.pop_back();
}

void sub1(vector<int>& a) {
    for (int i = 0, carry = 0; i < a.size() || carry; ++i) {
        a[i] -= carry + (i == 0 ? 1 : 0);
        carry = a[i] < 0;
        if (carry) a[i] += 10;
    }
    while (a.size() >= 2 && a.back() == 0) a.pop_back();
}

int main() {
    freopen("rsa.in", "r", stdin);
    freopen("rsa.out", "w", stdout);

    int t, m;
    scanf("%d%d", &t, &m);

    vector<int> b(m);
    for (int i = 0; i < m; ++i) {
        scanf("%d", &b[i]);
    }

    auto primes = get_primes(100);

    vector<bitset<N>> a(t);
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < primes.size(); ++j) {
            int p = primes[j];
            while (b[i] % p == 0) {
                a[j].flip(i);
                b[i] /= p;
            }
        }
    }

    int rank = get_rank(a, t, m);
    int q = m - rank;
    vector<int> d(1, 1);
    for (int i = 0; i < q; ++i) {
        mult2(d);
    }
    sub1(d);
    for (int i = d.size() - 1; i >= 0; --i) {
        printf("%d", d[i]);
    }
    puts("");
}
