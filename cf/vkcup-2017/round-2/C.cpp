#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <string>
#define X first
#define Y second
 
using namespace std;
 
typedef long long ll;
 
const ll dd = 1e6;
const ll inf = 1e9 + 7;
 
const double eps = 1e-8;

int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;
}
 
// TODO DEL DEBUG
#define _DEBUG
int main() {
#ifdef _DEBUG
    freopen("C.in", "r", stdin);
    freopen("C.out", "w", stdout);
#endif

    int m;
    for (int m = 1; m <= 9; ++m) {
        cout << "FA : " << m << endl;

        vector<int> a( m);
        for (int i = 0; i < m; i++) {
            a[i] = i;
        }

        set<int> forb = {};

        vector<int> my;
        set<int> qq;
        int curp = 1;
        while (true) {
            int sz = my.size();
            bool ok;
            do {
                ok = false;
                for (int i = 0; i < m; ++i) {
                    if (gcd(i, m) == 1) {
                        if ((curp * i) % m != 0)
                        if (forb.find((curp * i) % m) == forb.end() && qq.find((curp * i) % m) == qq.end()) {
                            curp = (curp * i) % m;
                            qq.insert(curp);
                            my.push_back(i);
                            ok = true;
                            break;
                        }
                    }
                }
            } while (ok);
            for (int i = 1; i < m; ++i) {
                if ((curp * i) % m != 0)
                if (forb.find((curp * i) % m) == forb.end() && qq.find((curp * i) % m) == qq.end()) {
                    curp = (curp * i) % m;
                    qq.insert(curp);
                    my.push_back(i);
                }
            }
            if (sz == my.size()) break;
        }
        if (forb.find(0) == forb.end() && qq.find(0) == qq.end()) {
            my.push_back(0);
        }


        vector<int> best;
        do {
            set<int> was;
            int p = 1;
            vector<int> cur;
            for (int i = 0; i < a.size(); ++i) {
                p = (p * a[i]) % m;
                if (forb.find(p) == forb.end() && was.find(p) == was.end()) {
                    cur.push_back(a[i]);
                    was.insert(p);
                } else {
                    break;
                }
            }
            if (best.size() < cur.size()) {
                best = cur;
            }
        } while (next_permutation(a.begin(), a.end()));
        sort(a.begin(), a.end());
        vector<vector<int>> all;
        do {
            set<int> was;
            int p = 1;
            vector<int> cur;
            for (int i = 0; i < a.size(); ++i) {
                p = (p * a[i]) % m;
                if (forb.find(p) == forb.end() && was.find(p) == was.end()) {
                    cur.push_back(a[i]);
                    was.insert(p);
                } else {
                    break;
                }
            }
            if (cur.size() == best.size()) {
                all.push_back(cur);
            }
        } while (next_permutation(a.begin(), a.end()));
        cout << best.size() << ' ' << my.size() << endl;
        for (int x : my) {
            cout << x << ' ';
        }
        cout << endl;

        /*
        for (auto& v : all) {
            for (int x : v) {
                cout << x << ' ';
            }
            cout << endl;
            break;
        }
        cout << endl;*/
    }
}
