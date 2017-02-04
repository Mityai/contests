#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MOD = 1 << 20;
const int X = 487237;
const int Y = 1011807;

int main() {
    srand(time(NULL));

    vector<int> zero, one;
    for (int i = 0; i < MOD; i++) {
        if (__builtin_popcount(i) % 2 == 0) {
            zero.push_back(i);
        } else {
            one.push_back(i);
        }
    }

    int money;
    cin >> money;

    int step = 0;
    while (true) {
        int bid;
        if (one.size() > zero.size()) {
            bid = int(money * (double) one.size() / double(one.size() + zero.size()));
        } else {
            bid = 1;
        }
        bid = max(1, min(200 - money, bid));
        if (step < 50) bid = 1;
        cout << bid << endl;
        cout.flush();

        step++;
        assert(step <= 200);

        int newmoney;
        cin >> newmoney;

        if (newmoney == -1) return 0;

        if (newmoney < money) {
            vector<int> nw;
            one.clear();
            for (int x : zero) {
                int newx = (X * 1LL * x + Y) % MOD;
                if (__builtin_popcount(newx) % 2 == 0) {
                    nw.push_back(newx);
                } else {
                    one.push_back(newx);
                }
            }
            zero = nw;
        } else {
            vector<int> nw;
            zero.clear();
            for (int x : one) {
                int newx = (X * 1LL * x + Y) % MOD;
                if (__builtin_popcount(newx) % 2 == 0) {
                    zero.push_back(newx);
                } else {
                    nw.push_back(newx);
                }
            }
            one = nw;
        }

        money = newmoney;
    }
}
