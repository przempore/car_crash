#ifndef CC_SERVER_HPP_
#define CC_SERVER_HPP_

#include <memory>
#include <string>

#include <grpcpp/grpcpp.h>

#include "car_crash.grpc.pb.h"
#include "rectangle.hpp"

namespace CC {

class CCGRPCService final : public carcrash::CarCrash::Service {
 public:
  ::grpc::Status GetNewId(::grpc::ServerContext *context,
                          const ::google::protobuf::Empty *request,
                          ::carcrash::Id *response) final {
    response->set_id(vehicles_.size());
    return ::grpc::Status::OK;
  }

  ::grpc::Status GetVehicles(::grpc::ServerContext *context,
                             const ::google::protobuf::Empty *request,
                             ::carcrash::Vehicles *response) final {
    return ::grpc::Status::OK;
  }

  ::grpc::Status UpdateVehicle(::grpc::ServerContext *context,
                               const ::carcrash::VehicleWithId *request,
                               ::google::protobuf::Empty *response) final {
    return ::grpc::Status::OK;
  }

 private:
  std::vector<Rectangle> vehicles_;
};

class Server final {
 public:
  explicit Server(std::string server_address = "0.0.0.0:50051") : server_address_{std::move(server_address)} {}

  ~Server() {
    server_->Shutdown();
  }

  void run() {
    grpc::ServerBuilder builder;
    builder.AddListeningPort(server_address_, grpc::InsecureServerCredentials());
    builder.RegisterService(&service_);
    server_ = builder.BuildAndStart();
    std::cout << "Server listening on " << server_address_ << std::endl;

    server_->Wait();
  }

 private:
  std::string server_address_;
  CCGRPCService service_;
  std::unique_ptr<grpc::Server> server_;
};

}

#endif //CC_SERVER_HPP_
