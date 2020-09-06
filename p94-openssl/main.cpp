// #include <boost/asio.hpp>
#include <iostream>
#include "sign.h"
#include "verify.h"
#include <boost/program_options.hpp>
#include <fstream>

namespace po = boost::program_options;

std::string read_file(std::string file_path){
  std::ifstream file (file_path, std::ios::in);
  std::string line;
  std::string output = "";
  if (file.is_open())
  {
    while ( std::getline (file,line) )
    {
      output += line + "\n";
    }
    file.close();
  }
  return output;
}

char* read_binary_file(std::string file_path) {
  std::streampos size;
  char *memblock;

  std::ifstream file(file_path.c_str(),
                     std::ios::in | std::ios::binary | std::ios::ate);
  if (file.is_open()) {
    size = file.tellg();
    memblock = new char[size];
    file.seekg(0, std::ios::beg);
    file.read(memblock, size);
    file.close();

    std::cout << "the entire file content is in memory";
    //delete[] memblock;
  }
  return memblock;
}

void write_file(std::string file_path, char* content) {
  std::ofstream file;
  file.open(file_path, std::ios::out);
  file << content;
  file.close();
}

void write_binary_file(std::string file_path, unsigned char *content) {
  std::ofstream file;
  file.open(file_path, std::ios::out | std::ios::binary);
  file << content;
  file.close();
}

int main(int argc, char *argv[]){
  po::options_description desc("Allowed options");
  desc.add_options()
    ("help,h", "help message")
    ("version,v", "display version");

  po::options_description cmdline("Command");
  desc.add_options()
    ("sign,S", "sign")
    ("verify,V", "verify")
    ("data,d", po::value<std::string>(), "data")
    ("signature,s", po::value<std::string>(), "signature")
    ("public-key,P", po::value<std::string>(), "public-key")
    ("private-key,p", po::value<std::string>(), "private-key")
    ;

  po::options_description cmdline_options;
  cmdline_options.add(desc).add(cmdline);

  po::variables_map vm;
  try{
    auto parsed_options = po::command_line_parser(argc, argv).options(cmdline_options).run();
    po::store(parsed_options, vm);
    po::notify(vm);
  }catch(boost::wrapexcept<boost::program_options::unknown_option> e){
    std::cout << e.what() << std::endl; 
    return 1;
  }
  //version
  if (vm.count("version")) {
    std::cout << 0.1 << std::endl;
    return 0;
  }

  //help
  if (vm.count("help")) {
    std::cout << desc << "\n";
    return 0;
  }

  //opensll
  if(vm.count("sign")){
    std::string private_key_path = vm["private-key"].as<std::string>();
    std::string data_path = vm["data"].as<std::string>();

    std::string privateKeyStr = read_file(private_key_path);
    std::string dataStr = read_file(data_path);
    
    auto msg = signMessage(privateKeyStr, dataStr);
    write_file("signature.txt", msg);
    //write_binary_file("signature.txt", msg);
  }else if(vm.count("verify")){
    std::string public_key_path = vm["public-key"].as<std::string>();
    std::string data_path = vm["data"].as<std::string>();
    std::string signature_path = vm["signature"].as<std::string>();

    std::string publicKey = read_file(public_key_path);
    std::string dataStr = read_file(data_path);
    std::string signatureChar = read_file(signature_path);
    //char *signatureChar = read_binary_file(signature_path);

    std::cout << "publicKey: " << publicKey << std::endl;
    std::cout << "dataStr: " << dataStr << std::endl;
    std::cout << "signatureChar: " << signatureChar << std::endl;

    bool authentic = verifySignature(publicKey, dataStr, (char *)signatureChar.c_str());
    if (authentic){
      std::cout << "WONDERFUL" << std::endl;
    }else{
      std::cout << "You hacker, you..." << std::endl;
    }
  }

  return 0;
}