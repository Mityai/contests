#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

int main() {
    freopen("mooo.in", "r", stdin);
    freopen("mooo.out", "w", stdout);
    
    int n;
    cin >> n;
    vector<int> d(n), height(n), volume(n);
    stack<int> s;
    for (int i = 0; i < n; i++) {
        cin >> height[i] >> volume[i];
        if (s.empty()) {
            s.push(i);
        } else if (height[s.top()] > height[i]) {
            d[s.top()] += volume[i];
            s.push(i);
        } else {
            while (!s.empty()) {
                if (height[s.top()] > height[i]) break;
                s.pop();
            }
            if (!s.empty()) {
                d[s.top()] += volume[i];
            }
            s.push(i);
        }
    }
    while(!s.empty()) s.pop();
    for (int i = n-1; i >= 0; i--) {
        if (s.empty()) {
            s.push(i);
        } else if (height[s.top()] > height[i]) {
            d[s.top()] += volume[i];
            s.push(i);
        } else {
            while (!s.empty()) {
                if (height[s.top()] > height[i]) break;
                s.pop();
            }
            if (!s.empty()) {
                d[s.top()] += volume[i];
            }
            s.push(i);
        }
    }

    cout << *max_element(d.begin(), d.end());

    return 0;
}