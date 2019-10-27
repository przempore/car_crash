#include <thread>

#include <network/cc_server.hpp>

int main(int argc, char **argv) {
  std::thread server_thr([]() {
    CC::Server server;
    server.run();
  });
  server_thr.join();

  return 0;
}
