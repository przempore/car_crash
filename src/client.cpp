#include <thread>

#include <network/cc_client.hpp>
#include <details/mainLoop.hpp>

int main(int argc, char **argv) {
  std::thread clients_thr([]() {
    CC::Client(grpc::CreateChannel(
        "localhost:50051", grpc::InsecureChannelCredentials()));
  });

  std::thread game_thr([]() {
    return CC::mainLoop();
  });

  clients_thr.join();
  game_thr.join();

  return 0;
}
