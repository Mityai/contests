#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<vector<int>> M;

int p;

M operator * (const M& A, const M& B) {
    M C(A.size(), vector<int>(B[0].size()));
    for (int i = 0; i < C.size(); ++i) {
        for (int j = 0; j < C[i].size(); ++j) {
            for (int k = 0; k < B.size(); ++k) {
                C[i][j] += (A[i][k] * 1ll * B[k][j]) % p;
                if (C[i][j] >= p) C[i][j] -= p;
            }
        }
    }
    return C;
}

struct BigInt {
    vector<int> d;

    BigInt(const string& s) {
        for (int i = int(s.size()) - 1; i >= 0; --i) {
            d.push_back(s[i] - '0');
        }
    }
};

bool iszero(const BigInt& a) {
    return a.d.empty();
}

bool odd(const BigInt& a) {
    return a.d[0] & 1;
}

void div2(BigInt& a) {
    auto& d = a.d;
    if (d[0] & 1) d[0] ^= 1;
    while (!d.empty() && d.back() == 0) d.pop_back();
    if (d.empty()) return;
    for (int i = d.size() - 1, carry = 0; i >= 0; --i) {
        int cur = d[i] + carry * 10;
        d[i] = cur / 2;
        carry = cur & 1;
    }
    while (!d.empty() && d.back() == 0) d.pop_back();
}

void print(const BigInt& a) {
    auto& d = a.d;
    for (int i = int(d.size()) - 1; i >= 0; --i) {
        cout << d[i];
    }
    cout << endl;
}

M bin_pow(M A, BigInt& n) {
    M ans = M(A.size(), vector<int>(A.size()));
    for (size_t i = 0; i < A.size(); ++i) ans[i][i] = 1 % p;
    while (!iszero(n)) {
        if (odd(n)) ans = ans * A;
        A = A * A;
        div2(n);
    }
    return ans;
}

int main() {
    string s;
    cin >> s;
    BigInt n(s);
    int m;
    scanf("%d%d", &m, &p);

    const int N = 1 << m;
    M A(N, vector<int>(N));
    for (int prev = 0; prev < N; ++prev) {
        for (int mask = 0; mask < N; ++mask) {
            bool ok = true;
            for (int i = 0; i + 1 < m; ++i) {
                int cur = (prev >> i) & 1;
                cur += (prev >> (i + 1)) & 1;
                cur += (mask >> i) & 1;
                cur += (mask >> (i + 1)) & 1;
                if (cur % 4 == 0) {
                    ok = false;
                    break;
                }
            }
            if (ok) {
                ++A[prev][mask];
            }
        }
    }

    M f(1, vector<int>(N));
    int mask = 0;
    for (int i = 0; i < m; i += 2) {
        mask |= (1 << i);
    }
    f[0][mask] = 1;

    f = f * bin_pow(A, n);
    int ans = 0;
    for (int i = 0; i < N; ++i) {
        ans = (ans + f[0][i]) % p;
    }
    printf("%d\n", ans);
}
