#include <network/cc_async_server.hpp>

int main(int argc, char** argv) {
  ServerImpl server;
  server.Run();

  return 0;
}
