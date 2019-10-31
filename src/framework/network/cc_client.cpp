#include "cc_client.hpp"

namespace CC {

GRPCClient::GRPCClient(std::shared_ptr<::grpc::Channel> channel) : stub_(carcrash::CarCrash::NewStub(channel)) {}

uint32_t GRPCClient::getId() {
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

std::vector<Rectangle> GRPCClient::getVehicles() {
  ::grpc::ClientContext context;
  ::carcrash::Vehicles reply;
  ::grpc::Status status = stub_->GetVehicles(&context, ::google::protobuf::Empty(), &reply);

  return std::vector<Rectangle>();
}

Client::Client(const std::string &ip) : client_(grpc::CreateChannel(ip, grpc::InsecureChannelCredentials())) {}

uint32_t Client::getId() {
  return client_.getId();
}

std::vector<Rectangle> Client::getVehicles() {
  return client_.getVehicles();
}

}

