#include <iostream>

int main()  {
  int a, b;
  std::cin >> a >> b;
  if ((a + b) % 100 == 0)
    std::cout << "unlucky today" << std::endl;
  std::cout << a + b << std::endl;
  return 0;
}
