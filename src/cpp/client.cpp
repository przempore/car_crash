#include <iostream>
#include <regex>
#include <string>

#include "framework/details/mainLoop.hpp"

int main(const int argc, const char** argv) {
  std::string ip = "localhost:50051";
  if (argc > 1) {
    const std::regex ip_regex(
        R"(((\d{1,3}(\.\d{1,3}){3})|(localhost))\:\d{2,5})");
    ip = argv[1];

    std::smatch base_match;
    if (!std::regex_match(ip, base_match, ip_regex)) {
      std::cerr << "Usage: car_crash_client <ip_address:with_port>";
      return -1;
    }
  }

  CC::ClientConfig config;
  config.ip = ip;
  return CC::mainLoop();
}
