#include <bits/stdc++.h>
using namespace std;

int main() {
  int n;
  cin >> n;

  int a[n];
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }

  for (int i = 0; i < n; i++) {
    int mn = i;
    for (int j = i + 1; j < n; j++) {
      if (a[mn] > a[j]) {
        mn = j;
      }
    }
    for (int j = mn; j > i; j--) {
      printf("%d %d\n", j, j + 1);
      swap(a[j], a[j - 1]);
    }
  }
}
