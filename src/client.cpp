#include <thread>

#include <details/mainLoop.hpp>

bool mainLoopThread(const std::string& ip) {
  CC::ClientConfig config;
  config.ip = ip;
  return CC::mainLoop();
}

int main(int argc, char **argv) {
  if (argc > 1) {
  	const std::string ip = argv[1];
  	std::thread game_thr(mainLoopThread, ip);
  	game_thr.join();
  } else {
  	std::thread game_thr(mainLoopThread, "localhost:50051");
  	game_thr.join();
  }

  return 0;
}
