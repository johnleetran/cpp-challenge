#include <iostream>
#include <numeric>
#include <vector>
#include <algorithm>

int find_gcd(int num1, int num2) {
  int div = 1;
  int min_num = std::min(num1, num2);
  int max_num = std::max(num1, num2);

  for (int i = min_num; i >= 1; i--) {
      int tmp_div = min_num % i;
      if (tmp_div == 0 && max_num % i == 0) {
          return i;
      }
  }
  return div;
}

int main(int argc, char *argv[]) {
  int num1 = std::atoi(argv[1]);
  int num2 = std::atoi(argv[2]);

  int gcd = find_gcd(num1, num2);
      std::cout << "gcd: " << gcd << std::endl;
}