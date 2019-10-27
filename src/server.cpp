#include <thread>

#include <network/cc_async_server.hpp>

int main(int argc, char **argv) {
  std::thread server_thr([]() {
    ServerImpl server;
    server.Run();
  });
  server_thr.join();

  return 0;
}
