#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <map>
#include <algorithm>
#include <vector>
#define ll long long
using namespace std;

struct School {
    int num_;
    int kol_;
};

bool cmp(School a, School b) {
    return a.kol_ > b.kol_;
}

int main() {
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    
    int n;
    cin >> n;
    map<int, int> sch;
    for (int i = 0; i < n; i++) {
        int num;
        cin >> num;
        sch[num]++;
        if (sch[num] > n/2+n%2) {
            cout << 0;
            return 0;
        }
    }

    vector<School> lst;
    for (map<int, int>::iterator it = sch.begin(); it != sch.end(); it++) {
        School s; s.num_ = it->first; s.kol_ = it->second;
        lst.push_back(s);
    }

    sort(lst.begin(), lst.end(), cmp);
    vector<int> ans(n);
    int k = 0;
    for (int i = 0; i < ans.size(); i += 2) {
        if (lst[k].kol_ == 0) {
            k++;
        }
        ans[i] = lst[k].num_;
        lst[k].kol_--;
    }
    for (int i = 1; i < ans.size(); i += 2) {
        if (lst[k].kol_ == 0) {
            k++;
        }
        ans[i] = lst[k].num_;
        lst[k].kol_--;
    }
    for (int i = 0; i < ans.size(); i++) {
        cout << ans[i] << endl;
    }

    return 0;
}