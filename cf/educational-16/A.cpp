#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

const int dx[] = {-1, -1, 0, 1, 1, 1, 0, -1};
const int dy[] = {0, -1, -1, -1, 0, 1, 1, 1};

int main() {
#if __APPLE__
#endif

  char c; int d;
  scanf(" %c%d", &c, &d);
  int i = c - 'a';
  int j = d - 1;

  int ans = 0;
  for (int k = 0; k < 8; k++) {
    int newi = i + dx[k];
    int newj = j + dy[k];
    if (0 <= newi && newi < 8 && 0 <= newj && newj < 8) ans++;
  }
  cout << ans << endl;
}
