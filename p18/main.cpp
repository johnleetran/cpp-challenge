
#include <functional>
#include <iostream>
#include <limits>
#include <vector>

template <typename T> 
T find_min(T a, T b){
  return std::min(a, b);
}

template <typename T, typename... Types> 
T find_min(T t, Types... ts){
  return (find_min(t, find_min(ts...)));
}

template <class Compare, typename T>
T minimumc(Compare comp, T const a, T const b) {
  return comp(a, b) ? a : b;
}

template <class Compare, typename T1, typename... T>
T1 minimumc(Compare comp, T1 a, T... args) {
  return minimumc(comp, a, minimumc(comp, args...));
}

// T find_min(T t, Types... ts) {
//   T min = t;
//   std::vector<T> vec = {ts...};
//   for (auto ele : vec) {
//     if (ele < min) {
//       min = ele;
//     }
//   }
//   return min;
// }

int main(int argc, char *argv[]) {
  int min = find_min(6, 2, -4, 8, -2);
  std::cout << "min: " << min << std::endl;

  min = minimumc(std::less<>(), 6, 2, -4, 8, -2);
  std::cout << "min: " << min << std::endl;
  return 0; 
}