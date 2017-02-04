#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>

typedef long long ll;

using namespace std;

int n;

void print(vector<int> a) {
    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

void rec(int i, vector<int> a) {
    if (i == n) {
        print(a);
        return;
    }

    for (int j = i; j < n; j++) {
        swap(a[i], a[j]);
        rec(i + 1, a);
    }

    for (int j = 0; j < n - 1; j++) {
        swap(a[j], a[j + 1]);
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    scanf("%d", &n);
    
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        a[i] = i + 1;
    }

    rec(0, a);
}