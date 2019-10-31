#ifndef CC_CLIENT_HPP_
#define CC_CLIENT_HPP_

#include <grpcpp/grpcpp.h>
#include "car_crash.grpc.pb.h"
#include "rectangle.hpp"

namespace CC {

class GRPCClient {
 public:
  explicit GRPCClient(std::shared_ptr<::grpc::Channel> channel);

  uint32_t getId();
  std::vector<Rectangle> getVehicles();

 private:
  std::unique_ptr<carcrash::CarCrash::Stub> stub_;
};

class Client {
 public:
  explicit Client(const std::string& ip = "localhost:50051");
  uint32_t getId();
  std::vector<Rectangle> getVehicles();

 private:
  GRPCClient client_;
};

};

#endif //CC_CLIENT_HPP_
