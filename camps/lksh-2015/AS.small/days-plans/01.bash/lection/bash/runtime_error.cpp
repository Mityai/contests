#include <cstdio>
#include <cstdlib>
#include <chrono>

int main(){
  /** Java: Random r = new Random(); r.nextInt() */
  srand(std::chrono::system_clock::now().time_since_epoch().count());
  if (rand() % 100 == 0)
    return 1;
  puts("Yes =)");
  return 0;
}
