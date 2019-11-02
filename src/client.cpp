#include <thread>

#include <details/mainLoop.hpp>

bool mainLoopThread() {
  return CC::mainLoop();
}

int main(int argc, char **argv) {
  std::thread game_thr(mainLoopThread);

  game_thr.join();

  return 0;
}
