#include <thread>

#include <details/mainLoop.hpp>
#include <network/cc_async_server.hpp>

int main(int argc, char **argv) {
  std::thread server_thr([]() {
    ServerImpl server;
    server.Run();
  });

  std::thread game_thr([]() {
    return mainLoop();
  });

  server_thr.join();
  game_thr.join();

  return 0;
}
