// #include <boost/asio.hpp>
#include <iostream>
#include <curl/curl.h>
#include <stdlib.h>
#include <boost/program_options.hpp>
#include <vector>
#include <fstream>
#include <sys/stat.h>
#include <fcntl.h>

namespace po = boost::program_options;
const std::string MY_VERSION = "0.1";
struct CurlRequestOptions{
  std::string data;
};

int call_get(std::string url, std::vector<std::string> headers) {
  CURL *curl;
  CURLcode res;
  curl = curl_easy_init();
  if(curl) {
    struct curl_slist *chunk = NULL;

    for(auto &header : headers){
      //std::cout << header << std::endl;
      chunk = curl_slist_append(chunk, header.c_str());
    }

    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
 
    res = curl_easy_perform(curl);
    /* Check for errors */ 
    if(res != CURLE_OK){
      fprintf(stderr, "curl_easy_perform() failed: %s\n",curl_easy_strerror(res));
    }
 
    /* always cleanup */ 
    curl_easy_cleanup(curl);
 
    /* free the custom headers */ 
    curl_slist_free_all(chunk);
  }
  return 0;
}

int call_post(std::string url, std::vector<std::string> headers, std::string infile)
{
  CURL *curl;
  CURLcode res;
  struct stat file_info;
  curl_off_t speed_upload, total_time;
  FILE *fd;
 
  fd = fopen(infile.c_str(), "rb"); /* open file to upload */ 
  if(!fd)
    return 1; /* can't continue */ 
 
  /* to get the file size */ 
  if(fstat(fileno(fd), &file_info) != 0)
    return 1; /* can't continue */ 
 
  curl = curl_easy_init();
  if(curl) {
    /* upload to this place */ 
    curl_easy_setopt(curl, CURLOPT_URL,
                     url.c_str());
 
    struct curl_slist *chunk = NULL;

    for(auto &header : headers){
      //std::cout << header << std::endl;
      chunk = curl_slist_append(chunk, header.c_str());
    }
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);

    /* tell it to "upload" to the URL */ 
    curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
 
    /* set where to read from (on Windows you need to use READFUNCTION too) */ 
    curl_easy_setopt(curl, CURLOPT_READDATA, fd);
 
    /* and give the size of the upload (optional) */ 
    curl_easy_setopt(curl, CURLOPT_INFILESIZE_LARGE,
                     (curl_off_t)file_info.st_size);
 
    /* enable verbose for easier tracing */ 
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
 
    res = curl_easy_perform(curl);
    /* Check for errors */ 
    if(res != CURLE_OK) {
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
 
    }
    else {
      /* now extract transfer info */ 
      curl_easy_getinfo(curl, CURLINFO_SPEED_UPLOAD_T, &speed_upload);
      curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME_T, &total_time);
 
      fprintf(stderr, "Speed: %" CURL_FORMAT_CURL_OFF_T " bytes/sec during %"
              CURL_FORMAT_CURL_OFF_T ".%06ld seconds\n",
              speed_upload,
              (total_time / 1000000), (long)(total_time % 1000000));
 
    }
    /* always cleanup */ 
    curl_easy_cleanup(curl);
    /* free the custom headers */ 
    curl_slist_free_all(chunk);
  }
  fclose(fd);
  return 0;
}

int main(int argc, char *argv[]){
  po::options_description desc("Allowed options");
  desc.add_options()
    ("help,h", "help message")
    ("version,v", "display version");

  po::options_description cmdline("Command");
  desc.add_options()
    ("header,H", po::value< std::vector<std::string> >(), "http header")
    ("method,X", po::value<std::string>(), "method")
    ("data,d", po::value<std::string>(), "data")
    ("url,u", po::value<std::string>(), "url")
    ;

  po::options_description cmdline_options;
  cmdline_options.add(desc).add(cmdline);

  po::positional_options_description p;
  p.add("url", -1);

  po::variables_map vm;
  try{
    auto parsed_options = po::command_line_parser(argc, argv).options(cmdline_options).positional(p).run();
    po::store(parsed_options, vm);
    po::notify(vm);
  }catch(boost::wrapexcept<boost::program_options::unknown_option> e){
    std::cout << e.what() << std::endl; 
    return 1;
  }


  //help
  if (vm.count("help")) {
    std::cout << desc << "\n";
    return 0;
  }

  //version
  if (vm.count("version")) {
    std::cout << MY_VERSION << std::endl;
    return 0;
  }

  std::string url = vm["url"].as<std::string>();

  std::vector<std::string> headers;
  if(vm.count("header")){
    headers = vm["header"].as<std::vector<std::string> >();
  }

  if(vm.count("method")){
    std::string method = vm["method"].as<std::string>();
    if(method == "POST"){
      //CurlRequestOptions curl_request_options{};
      //std::ifstream infile(vm["data"].as<std::string>());
      std::string infile = vm["data"].as<std::string>();
      call_post(url, headers, infile);
    }else{
      call_get(url, headers);
    }
  }else{
    call_get(url, headers);
  }
  // if( vm.count("header")) {
  //   std::vector<std::string> headers = vm["header"].as<std::vector<std::string> >();
  //     std::cout << "Headers" << std::endl;
  //   for(auto &header : headers){
  //     std::cout << header << std::endl;
  //   }
  // }

  // if (vm.count("url"))
  // {
  //     std::cout << "URL: " << vm["url"].as<std::string>() << std::endl;
  // }

  return 0;
}