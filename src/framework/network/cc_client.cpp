#include "cc_client.hpp"

#include <limits>

namespace CC {

GRPCClient::GRPCClient(std::shared_ptr<::grpc::Channel> channel) : stub_(carcrash::CarCrash::NewStub(channel)) {}

uint32_t GRPCClient::getId() {
  ::grpc::ClientContext context;
  ::carcrash::Id reply;
  ::grpc::Status status = stub_->GetNewId(&context, ::google::protobuf::Empty(), &reply);

  if (!status.ok()) {
    std::cout << status.error_code() << ": " << status.error_message()
              << std::endl;
    return std::numeric_limits<uint32_t>::infinity();
  }

  return reply.id();
}

std::vector<Rectangle> GRPCClient::getVehicles() {
  ::grpc::ClientContext context;
  ::carcrash::Vehicles reply;
  ::grpc::Status status = stub_->GetVehicles(&context, ::google::protobuf::Empty(), &reply);

  //auto rectangles = reply.rectangles();
  if (!status.ok()) {
    std::cout << status.error_code() << ':' << status.error_message() << '\n';
    return {};
  }

  std::vector<Rectangle> rectangles;
  std::transform(reply.rectangles().begin(), reply.rectangles().end(), std::back_inserter(rectangles), [](const auto& r) { return copyFromGrpc(r); });

  return rectangles;
}

uint32_t GRPCClient::updateVehicle(uint32_t id, const Rectangle& vehicle) {
  ::grpc::ClientContext context;
  ::carcrash::VehicleWithId request;
  ::google::protobuf::Empty empty;

  ::carcrash::Rectangle rectangle;
  rectangle.CopyFrom(copyToGrpc(vehicle));

  *request.mutable_rectangle() = rectangle;

  ::carcrash::Id request_id;
  request_id.set_id(id);

  *request.mutable_id() = request_id;

  ::grpc::Status status = stub_->UpdateVehicle(&context, request, &empty);

  if (!status.ok()) {
    std::cout << status.error_code() << ": " << status.error_message()
              << std::endl;
    return std::numeric_limits<uint32_t>::infinity();
  }

  return id;
}

uint32_t GRPCClient::registerVehicle(const Rectangle& vehicle) {
  ::grpc::ClientContext context;
  ::carcrash::VehicleWithId request;
  ::carcrash::Rectangle rectangle;
  rectangle.CopyFrom(copyToGrpc(vehicle));

  *request.mutable_rectangle() = rectangle;

  ::carcrash::Id id;
  id.set_id(vehicle.id);

  *request.mutable_id() = id;
  ::carcrash::Id reply;
  ::grpc::Status status = stub_->RegisterVehicle(&context, request, &reply);

  if (!status.ok()) {
    std::cout << status.error_code() << ": " << status.error_message()
              << std::endl;
    return std::numeric_limits<uint32_t>::infinity();
  }

  return reply.id();
}

uint32_t GRPCClient::unregisterVehicle(uint32_t id) {
  ::grpc::ClientContext context;
  ::carcrash::Id request;
  ::carcrash::Id reply;

  request.set_id(id);
  ::grpc::Status status = stub_->UnregisterVehicle(&context, request, &reply);

  if (!status.ok()) {
    std::cout << status.error_code() << ": " << status.error_message()
              << std::endl;
    return std::numeric_limits<uint32_t>::infinity();
  }

  return reply.id();
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

uint32_t Client::unregisterVehicle(uint32_t id) {
  return client_.unregisterVehicle(id);
}

}

