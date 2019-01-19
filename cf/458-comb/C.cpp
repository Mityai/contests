#include <iostream>
#include <string>

using namespace std;

const int N = 1000 + 1;
const int MOD = 1e9 + 7;

int cnk[N][N];
int steps[N];

int get(int x) {
    int res = 0;
    while (x != 1) {
        x = __builtin_popcount(x);
        ++res;
    }
    return res;
}

void calc() {
    for (int i = 0; i < N; ++i) {
        cnk[i][0] = cnk[i][i] = 1;
        if (i > 0) {
            for (int j = 1; j < i; ++j) {
                cnk[i][j] = (cnk[i - 1][j - 1] + cnk[i - 1][j]) % MOD;
            }
        }
    }

    steps[0] = -228;
    for (int i = 1; i < N; ++i) {
        steps[i] = get(i);
    }
}

int main() {
    ios_base::sync_with_stdio(false);

    calc();

    string n;
    cin >> n;

    int k;
    cin >> k;

    if (k == 0) {
        cout << 1 << endl;
        return 0;
    }

    int ans = 0;
    int one = 0;
    for (int i = 0; i < n.length(); ++i) {
        if (n[i] != '1') continue;

        int m = n.length() - i;
        for (int j = 0; j <= m - 1; ++j) {
            if (steps[one + j] + 1 == k) {
                ans += cnk[m - 1][j];
                if (ans >= MOD) ans -= MOD;
            }
        }

        ++one;
    }

    ans += (steps[one] + 1 == k);
    if (k == 1) {
        --ans;
    }

    cout << ans << endl;
}
