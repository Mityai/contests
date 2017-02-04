#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <algorithm>
#include <map>
using namespace std;
 
int main() {
    freopen("records.in", "r", stdin);
    freopen("records.out", "w", stdout);
    
    int n;
    cin >> n;
    map<string, int> ans;
    for (int i = 0; i < n; i++) {
        string temp[3];
        cin >> temp[0] >> temp[1] >> temp[2];
        sort(temp, temp+3);
        string group;
        group = temp[0]+temp[1]+temp[2];
        ans[group]++;
    }
    int mx = 0;
    for (map<string, int>::iterator it = ans.begin(); it != ans.end(); it++) {
        mx = max(mx, it->second);
    }
    cout << mx;

    return 0;
}