#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <cstdio>
#include <cmath>
#include <vector>
#include <set>
#include <string>
using namespace std;

struct Work {
    int d;
    int w;
    int pos;
    int day;
};

bool cmp(Work a, Work b) {
    if (a.w == b.w) {
        return a.d < b.d;
    }
    return a.w > b.w;
}

bool cmp2(Work a, Work b) {
    return a.pos < b.pos;
}
 
int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    
    int n;
    cin >> n;
    vector<Work> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i].d >> a[i].w;
        a[i].pos = i;
    }
    sort(a.begin(), a.end(), cmp);
    int shtr = 0;
    set<int> days;
    for (int i = 0; i < a.size(); i++) {
        int k = a[i].d;
        while (days.count(k) != 0 && k > 0) {
            k--;
        }
        if (k > 0) {
            days.insert(k);
            a[i].day = k;
        } else {
            shtr += a[i].w;
        }
    }
    int k = 1;
    for (int i = 0; i < a.size(); i++) {
        if (a[i].day == 0) {
            while (days.count(k) != 0) {
                k++;
            }
            days.insert(k);
            a[i].day = k;
        }
    }
    cout << shtr << endl;
    sort(a.begin(), a.end(), cmp2);
    for (int i = 0; i < a.size(); i++) {
        cout << a[i].day << " ";
    }

    return 0;
}