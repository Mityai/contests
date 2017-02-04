#include <bits/stdc++.h>
using namespace std;

const int N = 10;

int n;
int a[N][N];

void go(int &k) {
    k < n ? k++ : k = n;
}

void nothing() {
    // just nothing
}

void goj(int k, int i, int j) {
    a[i][j] = min(a[i][j], a[i][k] + a[k][j]);
    j++;
    j == n ? nothing() : goj(k, i, j);
}

void goi(int k, int i) {
    goj(k, i, 0);
    i++;
    i == n ? nothing() : goi(k, i);
}

void gok(int k) {
    goi(k, 0);
    k++;
    k == n ? nothing() : gok(k);
}

void pinkfloyd() {
    gok(0);
}

void readj(int i, int j) {
    cin >> a[i][j];
    j++;
    j == n ? nothing() : readj(i, j);
}

void readi(int i) {
    readj(i, 0);
    i++;
    i == n ? pinkfloyd() : readi(i);
}

int ans = 0;

void getmaxj(int i, int j) {
    ans = max(ans, a[i][j]);
    j++;
    j == n ? nothing() : getmaxj(i, j);
}

void getmaxi(int i) {
    getmaxj(i, 0);
    i++;
    i == n ? nothing() : getmaxi(i);
}

int main() {
    cin >> n;
    readi(0);
    getmaxi(0);
    cout << ans << endl;
}
