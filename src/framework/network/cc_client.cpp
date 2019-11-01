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

  auto rectangles = reply.rectangles();
  std::cout << __FILE__ << ':' << __LINE__;
  for (auto& r : rectangles) { std::cout << r.id() << ", "; }
  std::cout << '\n';
  if (status.ok()) {
    // todo: return reply->rectangles(); // translated to std::vector<Rectangle>
    return {};
  } else {
    std::cout << status.error_code() << ": " << status.error_message()
              << std::endl;
    return {};
  }

  return std::vector<Rectangle>();
}

uint32_t GRPCClient::updateVehicle(uint32_t id, const Rectangle& vehicle) {
  ::grpc::ClientContext context;
  ::carcrash::VehicleWithId request;
  ::google::protobuf::Empty empty;
  ::grpc::Status status = stub_->UpdateVehicle(&context, request, &empty);

  if (status.ok()) {
    return id;
  } else {
    std::cout << status.error_code() << ": " << status.error_message()
              << std::endl;
    return id;
  }
}

uint32_t GRPCClient::registerVehicle(const Rectangle& vehicle) {
  ::grpc::ClientContext context;
  ::carcrash::VehicleWithId request;
  ::carcrash::Rectangle rectangle;
  rectangle.CopyFrom(copyToGrpc(vehicle));

  auto& mut_rect = *request.mutable_rectangle();
  mut_rect = rectangle;

  ::carcrash::Id id;
  id.set_id(vehicle.id);

  auto& mut_id = *request.mutable_id();
  mut_id = id;
  ::carcrash::Id reply;
  ::grpc::Status status = stub_->RegisterVehicle(&context, request, &reply);

  if (status.ok()) {
    return reply.id();
  } else {
    std::cout << status.error_code() << ": " << status.error_message()
              << std::endl;
    return std::numeric_limits<uint32_t>::infinity();
  }
}

Client::Client(const std::string &ip) : client_(grpc::CreateChannel(ip, grpc::InsecureChannelCredentials())) {}

uint32_t Client::getId() {
  return client_.getId();
}

std::vector<Rectangle> Client::getVehicles() {
  return client_.getVehicles();
}

uint32_t Client::updateVehicle(uint32_t id, const Rectangle& vehicle) {
  return client_.updateVehicle(id, vehicle);
}

uint32_t Client::registerVehicle(const Rectangle& vehicle) {
  return client_.registerVehicle(vehicle);
}

}

