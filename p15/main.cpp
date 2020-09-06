#include <boost/asio.hpp>
#include <iostream>

int main(int argc, char *argv[]) {
  std::string ipAddress = std::string(argv[1]);
  boost::system::error_code ec;
  boost::asio::ip::address::from_string(ipAddress, ec);
  if (ec) {
    std::cerr << ec.message() << std::endl;
  } else {
    std::cout << "good" << std::endl;
  }
}