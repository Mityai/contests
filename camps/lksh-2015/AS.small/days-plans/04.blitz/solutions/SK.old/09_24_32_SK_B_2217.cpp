/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 * Date: 2012.07.03
 */

#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <vector>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)
#define Fill(a, x) memset(a, x, sizeof(a))
#define sz(a) (int)(a).size()

const int maxN = 2503;
const int maxV = 53;
const int maxD = maxV * 103;

char str[99];
int tn, f, n, m;
int d[maxV][1 << 13];
int qst[maxD], qen[maxD], q1[maxD][maxV], q2[maxD][maxV];
vector <int> to[maxV], w[maxV];

void add( int v, int pr, int D )
{
  if (d[v][pr] != -1 && d[v][pr] <= D)
    return;
  forn(i, 13)
    if (D && f && ((pr >> i) & 1) && (D - i) % 13 == 0)
      return;
  d[v][pr] = D;
  q1[D][qen[D]] = v;        
  q2[D][qen[D]++] = pr;
}

int main()
{
  scanf("%d", &tn);
  while (tn--)
  {
    scanf("%d%d", &n, &m);
    forn(i, maxV)
      to[i].clear(), w[i].clear();
    forn(i, m)
    {
      int a, b, c;
      scanf("%d%d%d", &a, &b, &c);
      to[a].push_back(b);
      w[a].push_back(c);
    }
    scanf("%s", str);
    f = !strcmp(str, "True");

    Fill(qst, 0);
    Fill(qen, 0);
    Fill(d, -1);
    add(1, 0, 0);
    forn(i, maxD)
      while (qst[i] < qen[i])
      {
        int v = q1[i][qst[i]];
        int pr = q2[i][qst[i]++];
        //printf("%d, %d : %d\n", v, pr, d[v][pr]);
        if (d[v][pr] != i)
          continue;
        //printf("%d, %d : %d\n", v, pr, d[v][pr]);
        forn(j, sz(to[v]))
        {
          int D = d[v][pr];
          int D1 = D + w[v][j];
          int v1 = to[v][j];
          int pr1 = pr | (1 << (D % 13));
          add(v1, pr1, D1);
        }
      }

    int ans = -1;
    forn(i, 1 << 13)
      if (d[n][i] != -1 && (ans == -1 || d[n][i] < ans))
        ans = d[n][i];
    printf("%d\n", ans);
  }
  return 0;
}
