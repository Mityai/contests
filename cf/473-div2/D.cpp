#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int N = 2e6;

vector<char> is_prime(N, true);

void gen_primes() {
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i < N; ++i) {
        if (is_prime[i]) {
            for (ll j = i * 1ll * i; j < N; j += i) {
                is_prime[j] = false;
            }
        }
    }
}

int next_prime(int x) {
    while (!is_prime[++x]);
    return x;
}

bool ok(int x, const unordered_set<int>& used_primes) {
    if (is_prime[x]) return true;
    for (int p = 2; p * 1ll * p <= x; ++p) {
        if (x % p == 0) {
            if (used_primes.find(p) != used_primes.end()) {
                return false;
            }
            while (x % p == 0) {
                x /= p;
            }
        }
    }
    if (x != 1) {
        if (used_primes.find(x) != used_primes.end()) {
            return false;
        }
    }
    return true;
}

int main() {
#if __APPLE__
    freopen("D.in", "r", stdin);
    freopen("D.out", "w", stdout);
#endif

    gen_primes();

    int n;
    scanf("%d", &n);

    vector<int> a(n);
    for (int& x : a) scanf("%d", &x);

    unordered_set<int> used_primes;
    bool imagine = false;
    bool second_greater = false;
    int last_prime;
    for (int ind = 0; ind < n; ++ind) {
        bool first_greater = false;
        if (!imagine) {
            int b = a[ind];
            vector<int> inserted;
            for (int p = 2; p * 1ll * p <= b; ++p) {
                if (b % p == 0) {
                    if (!used_primes.insert(p).second) {
                        first_greater = imagine = true;
                        break;
                    } else {
                        inserted.push_back(p);
                    }
                    while (b % p == 0) {
                        b /= p;
                    }
                }
            }
            if (!imagine) {
                if (b != 1) {
                    if (!used_primes.insert(b).second) {
                        first_greater = imagine = true;
                    }
                }
            }
            if (imagine) {
                for (int x : inserted) {
                    used_primes.erase(x);
                }
            }
        }
        if (imagine) {
            if (first_greater) {
                int b = a[ind];
                while (!ok(++b, used_primes));
                last_prime = b; // fake
                second_greater = true;
            } else if (second_greater) {
                last_prime = next_prime(1);
                second_greater = false;
            }
            while (used_primes.find(last_prime) != used_primes.end()) {
                last_prime = next_prime(last_prime);
            }
            printf("%d ", last_prime);
            if (is_prime[last_prime]) {
                used_primes.insert(last_prime);
            } else {
                int b = last_prime;
                for (int p = 2; p * 1ll * p <= b; ++p) {
                    if (b % p == 0) {
                        used_primes.insert(p);
                        while (b % p == 0) {
                            b /= p;
                        }
                    }
                }
                if (b != 1) {
                    used_primes.insert(b);
                }
            }
        } else {
            printf("%d ", a[ind]);
        }
    }
    putchar('\n');
}
