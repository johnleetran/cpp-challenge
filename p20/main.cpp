// #include <boost/asio.hpp>
#include <algorithm>
#include <assert.h>
#include <iostream>
#include <vector>

template <typename List, typename T>
bool contains_any(List list, T item) {
  return (std::find(std::begin(list), std::end(list), item) != std::end(list));
}

template <typename List, typename... Ts>
bool contains_any(List list, Ts... items) {
  return ( ... || contains_any(list, items));
}

int main(int argc, char *argv[]) {
  std::vector<int> i = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  assert(contains_any(i, 10, 11));
  return 0;
}