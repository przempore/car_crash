#include "cc_server.hpp"

namespace CC {

::grpc::Status CCGRPCService::GetNewId(::grpc::ServerContext*,
                                       const ::google::protobuf::Empty*,
                                       ::carcrash::Id* response) {
  // todo: id should be an atomic member to not send the same id to multiple
  // clients
  response->set_id(vehicles_.size());
  return ::grpc::Status::OK;
}

::grpc::Status CCGRPCService::GetVehicles(::grpc::ServerContext*,
                                          const ::google::protobuf::Empty*,
                                          ::carcrash::Vehicles* response) {
  for (auto& v : vehicles_) {
    auto* vehicle = response->add_rectangles();
    vehicle->CopyFrom(copyToGrpc(v.second));
  }
  return ::grpc::Status::OK;
}

::grpc::Status CCGRPCService::UpdateVehicle(
    ::grpc::ServerContext*, const ::carcrash::VehicleWithId* request,
    ::google::protobuf::Empty*) {
  const auto& id = request->id();

  vehicles_[id.id()] = copyFromGrpc(request->rectangle());
  checkForCollisions();

  return ::grpc::Status::OK;
}

::grpc::Status CCGRPCService::RegisterVehicle(
    ::grpc::ServerContext*, const ::carcrash::VehicleWithId* request,
    ::carcrash::Id*) {
  const auto& id = request->id();
  const auto& request_vehicle = request->rectangle();
  auto ret = vehicles_.emplace(id.id(), copyFromGrpc(request_vehicle));
  if (!ret.second) {
    std::cerr << __FILE__ << ':' << __LINE__
              << " | Can not insert rectangle with id: " << id.id() << '\n';
    return ::grpc::Status::CANCELLED;
  }
  return ::grpc::Status::OK;
}

::grpc::Status CCGRPCService::UnregisterVehicle(::grpc::ServerContext*,
                                                const ::carcrash::Id* request,
                                                ::carcrash::Id*) {
  uint32_t id = request->id();
  auto ret = vehicles_.erase(id);
  if (ret == 0) {
    std::cerr << __FILE__ << ':' << __LINE__
              << " | Could not erase vehicle with id: " << id
              << ", not such id.";
  }
  return ::grpc::Status::OK;
}

void CCGRPCService::checkForCollisions() {
  // for (size_t i = 0; i < vehicles_.size(); i++) {
  // for (size_t j = i; j < vehicles_.size(); j++) {
  // if (isCollided(vehicles_[i], vehicles_[j])) {
  // std::cerr << "vehicles_[" << i << "] and vehicles_[" << j
  //<< "] are colliding!\n";
  //}
  //}
  //}
}

Server::Server(std::string server_address)
    : server_address_{std::move(server_address)},
      service_{},
      server_{nullptr},
      latest_id_{0} {}

Server::~Server() { server_->Shutdown(); }

void Server::run() {
  grpc::ServerBuilder builder;
  builder.AddListeningPort(server_address_, grpc::InsecureServerCredentials());
  builder.RegisterService(&service_);
  server_ = builder.BuildAndStart();
  std::cout << "Server listening on " << server_address_ << std::endl;

  server_->Wait();
}

}  // namespace CC
