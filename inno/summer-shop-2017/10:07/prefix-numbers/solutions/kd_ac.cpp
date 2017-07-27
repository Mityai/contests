#include<bits/stdc++.h>
using namespace std;
typedef unsigned int T;

const int mod = 4 * 7 * 9;

struct M {
  T t[mod][mod];
  M() {
    for(int i = 0; i < mod; ++i)
      for(int j = 0; j < mod; ++j)
        t[i][j] = 0;
  } 
  M operator * (M other) {
    M ans;
    for(int i = 0; i < mod; ++i)
      for(int j = 0; j < mod; ++j)
        for(int k = 0; k < mod; ++k)
          ans.t[i][k] += t[i][j] * other.t[j][k];
    return ans;
  }
};

int main() {
  M basic;
  for(int i = 0; i < mod; ++i)
    for(int dig = 1; dig <= 9; ++dig)
      if((i * 10 + dig) % dig == 0)
        ++basic.t[i][(i*10+dig)%mod];
  long long n;
  cin >> n;
  M answer;
  for(int i = 0; i < mod; ++i) answer.t[i][i] = 1;
  while(n) {
    if(n % 2) answer = answer * basic;
    basic = basic * basic;
    n /= 2;
  }
  T write = 0;
  for(int i = 0; i < mod; ++i)
    write += answer.t[0][i];
  cout << write << "\n";
  return 0;
}
