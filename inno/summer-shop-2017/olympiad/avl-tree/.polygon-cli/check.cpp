#include <bits/stdc++.h>
#include "testlib.h"

using namespace std;

vector<vector<int> > edges;
vector<int> hs;
vector<bool> was;
int n, h;

void check(int v, InStream &ouf) {
  if (v == n) return;
  if (was[v]) ouf.quitf(_wa, "Found cycle, expected tree");
  was[v] = 1;

  check(edges[v][0], ouf);
  check(edges[v][1], ouf);

  hs[v] = max(hs[edges[v][0]], hs[edges[v][1]]) + 1;

  if (abs(hs[edges[v][0]] - hs[edges[v][1]]) > 1)
    ouf.quitf(_wa, "Difference between the height of subtrees of descendants greater than 1");
}

bool readAnswer(int n, int h, InStream &ouf) {
  string pa = ouf.readToken();
  transform(pa.begin(), pa.end(), pa.begin(), ::tolower);
  if (pa != "yes" && pa != "no") {
    ouf.quitf(_wa, "Expected 'yes' or 'no'");
  }
  if (pa == "no") {
    return false;
  }

  edges.assign(n, vector<int>());

  for (int i = 1; i < n; i++) {
    int par = ouf.readInt(1, n, "Edge to parent") - 1;
    edges[par].push_back(i);
  }

  for (int i = 0; i < n; i++) {
    while ((int)edges[i].size() < 2) edges[i].push_back(n);
    if ((int)edges[i].size() > 2) ouf.quitf(_wa, "Binary tree expected");
  }

  hs.assign(n + 1, 0);
  was.assign(n, 0);

  check(0, ouf);

  if (find(was.begin(), was.end(), 0) != was.end()) {
    ouf.quitf(_wa, "Tree is not connected");
  }

  if (hs[0] != h) {
    ouf.quitf(_wa, "Heights do not match");
  }
  return true;
}

int main(int argc, char* argv[]) {
  registerTestlibCmd(argc, argv);

  n = inf.readInt();
  h = inf.readInt();

  bool ansJ = readAnswer(n, h, ans);
  bool ansP = readAnswer(n, h, ouf);

  if (ansJ == ansP) {
    quitf(_ok, "n = %d, h = %d", n, h);
  } else if (ansJ) {
    quitf(_wa, "Solution not found, n = %d, h = %d", n, h);
  } else {
    quitf(_fail, "Participant found solution, n = %d, h = %d", n, h);
  }
}
