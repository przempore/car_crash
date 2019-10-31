#include "cc_server.hpp"

namespace CC {

::grpc::Status CCGRPCService::GetNewId(::grpc::ServerContext *context,
                                       const ::google::protobuf::Empty *request,
                                       ::carcrash::Id *response) {
  response->set_id(vehicles_.size());
  return ::grpc::Status::OK;
}

::grpc::Status CCGRPCService::GetVehicles(::grpc::ServerContext *context,
                                          const ::google::protobuf::Empty *request,
                                          ::carcrash::Vehicles *response) {
  return ::grpc::Status::OK;
}

::grpc::Status CCGRPCService::UpdateVehicle(::grpc::ServerContext *context,
                                            const ::carcrash::VehicleWithId *request,
                                            ::google::protobuf::Empty *response) {
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

}