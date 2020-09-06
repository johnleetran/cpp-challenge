#include "iprange.h"
#include <cstring>
#include <fstream>
#include <iostream>
#include <vector>
#include <memory>

void write_to_file(std::string filename, std::string content) {
  std::ofstream MyFile(filename);

  // Write to the file
  MyFile << content << std::endl;

  // Close the file
  MyFile.close();
}

int main(int argc, char *argv[]) {

  std::string tmp_file_name = "ip_address.txt";
  std::string cidr = std::string(argv[1]);

  write_to_file(tmp_file_name, cidr);

  auto dst = std::make_unique<char[]>(tmp_file_name.length() + 1);
  std::strcpy(dst.get(), tmp_file_name.c_str());
  netaddr_to_range(dst.get());
  return 0;
}