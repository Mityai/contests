#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

const int K = 30;

struct Node {
  Node *nxt[2] = {nullptr, nullptr};
  int w = 0;
};

Node *root = new Node();

void add(int x) {
  Node *node = root;
  node->w++;
  for (int i = K; i >= 0; i--) {
    int f = ((x >> i) & 1);
    if (!node->nxt[f]) {
      node->nxt[f] = new Node();
    }
    node = node->nxt[f];
    node->w++;
  }
}

void del(int x) {
  Node *node = root;
  node->w--;
  for (int i = K; i >= 0; i--) {
    int f = ((x >> i) & 1);
    node = node->nxt[f];
    node->w--;
  }
}

int query(int x) {
  Node *node = root;
  int ans = 0;
  for (int i = K; i >= 0; i--) {
    int f = ((x >> i) & 1);
    if (node->nxt[1 - f] != nullptr && node->nxt[1 - f]->w != 0) {
      ans |= (1 << i);
      node = node->nxt[1 - f];
    } else {
      node = node->nxt[f];
    }
  }
  return ans;
}

int main() {
#if __APPLE__
  freopen("D.in", "r", stdin);
  freopen("D.out", "w", stdout);
#endif

  add(0);

  int q;
  scanf("%d", &q);

  for (int i = 0; i < q; i++) {
    char c;
    int x;
    scanf(" %c%d", &c, &x);

    if (c == '+') add(x);
    if (c == '-') del(x);
    if (c == '?') printf("%d\n", query(x));
  }
}
