#include <bits/stdc++.h>
#define monday sdfjhlasdasd
using namespace std;

const int D = 365;

bool isvis(int x) {
  return (x % 4 == 0 && x % 100 != 0) || x % 400 == 0;
}

void next(int &y, int &monday) {
  int days = D + isvis(y);
  monday = (monday + days) % 7;
  y++;
}

int main() {
  int x;
  cin >> x;

  int monday = 0;
  int y = x;
  next(y, monday);

  while (monday != 0 || isvis(x) != isvis(y)) {
    next(y, monday);
  }

  cout << y << endl;
}
