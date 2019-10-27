#include <thread>

#include <network/cc_async_client.hpp>
#include <details/mainLoop.hpp>

int main(int argc, char **argv) {
  std::thread clients_thr([]() {
    GreeterClient greeter(grpc::CreateChannel(
        "localhost:50051", grpc::InsecureChannelCredentials()));
    std::string user("world");
    std::string reply = greeter.SayHello(user);  // The actual RPC call!
    std::cout << "Greeter received: " << reply << std::endl;
  });

  std::thread game_thr([]() {
    return mainLoop();
  });

  clients_thr.join();
  game_thr.join();

  return 0;
}
