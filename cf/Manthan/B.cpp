#include <bits/stdc++.h>
using namespace std;

int main() {
    int m;
    scanf("%d", &m);

    vector<int> ans;
    for (int i = 1, cnt = 0; cnt <= m; i++) {
        int x = i;
        while (x % 5 == 0) {
            cnt++;
            x /= 5;
        }
        if (cnt == m) ans.push_back(i);
    }

    printf("%d\n", (int)ans.size());
    for (int x : ans) {
        printf("%d ", x);
    }
    puts("");
}
