#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

bool ispalind(vector<int> s) {
    for (int i = 0; i < (int)s.size() / 2; i++) {
        if (s[i] != s[(int)s.size() - i - 1]) return false;
    }
    return true;
}

vector<int> conv(int x, int p) {
    vector<int> ret;
    while (x > 0) {
        ret.push_back(x % p);
        x /= p;
    }
    reverse(ret.begin(), ret.end());
    return ret;
}

int main() {
    int x;
    scanf("%d", &x);

    set<int> ans;
    for (ll i = 1; i * i <= x; i++) {
        if (i >= 2 && ispalind(conv(x, i))) {
            ans.insert(i);
        }
        if (x % i == 0) {
            if (i - 1 >= 2 && ispalind(conv(x, i - 1))) {
                ans.insert(i - 1);
            }
            if (x / i - 1 >= 2 && ispalind(conv(x, x / i - 1))) {
                ans.insert(x / i - 1);
            }
        }
    }

    for (int x : ans) {
        printf("%d ", x);
    }
    puts("");
}
