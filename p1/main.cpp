#include <iostream>
#include <numeric>
#include <vector>

int main(int argc, char *argv[]) {
  int max = std::atoi(argv[1]) + 1;
  std::vector<int> numbers(max);
  std::iota(numbers.begin(), numbers.end(), 0);
  int sum = std::accumulate(numbers.begin(), numbers.end(), 0,
                            [](auto sum, auto num) {
                              if (num % 3 == 0 || num % 5 == 0) {
                                return sum += num;
                              } else {
                                return sum;
                              }
                            });
  std::cout << "sum: " << sum << std::endl;
}