#include "cc_server.hpp"

namespace CC {

::grpc::Status CCGRPCService::GetNewId(::grpc::ServerContext *context,
                                       const ::google::protobuf::Empty *request,
                                       ::carcrash::Id *response) {
  // todo: id should be an atomic member to not send the same id to multiple clients
  response->set_id(vehicles_.size());
  return ::grpc::Status::OK;
}

::grpc::Status CCGRPCService::GetVehicles(::grpc::ServerContext *context,
                                          const ::google::protobuf::Empty *request,
                                          ::carcrash::Vehicles *response) {
  for (auto& v : vehicles_) {
    auto* vehicle = response->add_rectangles();
    vehicle->CopyFrom(copyToGrpc(v));
  }
  return ::grpc::Status::OK;
}

::grpc::Status CCGRPCService::UpdateVehicle(::grpc::ServerContext *context,
                                            const ::carcrash::VehicleWithId *request,
                                            ::google::protobuf::Empty *response) {
  const auto& id = request->id();
  auto& vehicle_to_update = vehicles_[id.id()];
  const auto& request_vehicle = request->rectangle();
  vehicle_to_update = copyFromGrpc(request_vehicle);

  return ::grpc::Status::OK;
}


::grpc::Status CCGRPCService::RegisterVehicle(::grpc::ServerContext *context,
                                              const ::carcrash::VehicleWithId *request,
                                              ::carcrash::Id *response) {
  const auto& id = request->id();
  const auto& request_vehicle = request->rectangle();
  vehicles_.push_back(copyFromGrpc(request_vehicle));
  return ::grpc::Status::OK;
}

Server::Server(std::string server_address) : server_address_{std::move(server_address)} {}

Server::~Server() {
  server_->Shutdown();
}

void Server::run() {
  grpc::ServerBuilder builder;
  builder.AddListeningPort(server_address_, grpc::InsecureServerCredentials());
  builder.RegisterService(&service_);
  server_ = builder.BuildAndStart();
  std::cout << "Server listening on " << server_address_ << std::endl;

  server_->Wait();
}

}  // namespace CC
