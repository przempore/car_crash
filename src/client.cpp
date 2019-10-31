#include <thread>

#include <network/cc_client.hpp>
#include <details/mainLoop.hpp>

void clientThread() {
  CC::Client client;
  uint32_t id = client.getId();
}

bool mainLoopThread() {
  return CC::mainLoop();
}

int main(int argc, char **argv) {
  std::thread clients_thr(clientThread);
  std::thread game_thr(mainLoopThread);

  clients_thr.join();
  game_thr.join();

  return 0;
}
