#ifndef CC_CLIENT_HPP_
#define CC_CLIENT_HPP_

#include <grpcpp/grpcpp.h>
#include "car_crash.grpc.pb.h"

namespace CC {

class GRPCClient {
 public:
  explicit GRPCClient(std::shared_ptr<::grpc::Channel> channel) : stub_(carcrash::CarCrash::NewStub(channel)) {}

  uint32_t getId() {
    ::grpc::ClientContext context;
    ::carcrash::Id reply;
    ::grpc::Status status = stub_->GetNewId(&context, ::google::protobuf::Empty(), &reply);

    if (status.ok()) {
      return reply.id();
    } else {
      std::cout << status.error_code() << ": " << status.error_message()
                << std::endl;
      return std::numeric_limits<uint32_t>::infinity();
    }
  }

 private:
  std::unique_ptr<carcrash::CarCrash::Stub> stub_;
};

class Client {
 public:
  Client(const std::string& ip = "localhost:50051") : client_(grpc::CreateChannel(ip, grpc::InsecureChannelCredentials())) {}

  uint32_t getId() {
    return client_.getId();
  }

 private:
  GRPCClient client_;
};

};

#endif //CC_CLIENT_HPP_
