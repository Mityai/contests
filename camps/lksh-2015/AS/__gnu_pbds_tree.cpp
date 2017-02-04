
#include <cstdio>
#include <cassert>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

int main( void ) {
  assert(freopen("kthmax.in", "rt", stdin));
  assert(freopen("kthmax.out", "wt", stdout));

  int tn, t, x;
  tree<int, null_type, greater<int>, rb_tree_tag, tree_order_statistics_node_update> s;
  
  scanf("%d", &tn);
  while (tn--) {
    scanf("%d%d", &t, &x);
    if (t == 1)
      s.insert(x);
    else if (t == -1)
      s.erase(x);
    else 
      printf("%d\n", *s.find_by_order(x - 1)); // k-й максимум
  }
  return 0;
}

/** s.order_of_key(9999999) -- позиция ключа в дереве */


