#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

int main() {
    int n;
    scanf("%d", &n);

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    vector<pair<int, int>> b;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (a[i] == a[j]) {
                b.push_back({i, j});
            }
        }
    }
}
