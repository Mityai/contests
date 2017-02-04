#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>

#define pb push_back
#define pop pop_back

typedef long long ll;

using namespace std;

int n, k;

void print(vector<int> a) {
    for (size_t i = 0; i < a.size(); i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

void rec(vector<int> a) {
    if (int(a.size()) == k) {
        print(a);
        return;
    }

    int last = (a.empty() ? 0 : a.back());

    for (int i = last + 1; i <= n; i++) {
        a.pb(i);
        rec(a);
        a.pop();
    }
}

int main() {
    freopen("choose.in", "r", stdin);
    freopen("choose.out", "w", stdout);

    scanf("%d%d", &n, &k);

    vector<int> a;
    rec(a);
}