#ifndef CC_SERVER_HPP_
#define CC_SERVER_HPP_

#include <grpcpp/grpcpp.h>

#include <memory>
#include <string>
#include <unordered_map>

#include "car_crash.grpc.pb.h"
#include "rectangle.hpp"

namespace CC {

class CCGRPCService final : public carcrash::CarCrash::Service {
 public:
  ::grpc::Status GetNewId(::grpc::ServerContext* context,
                          const ::google::protobuf::Empty* request,
                          ::carcrash::Id* response) final;
  ::grpc::Status GetVehicles(::grpc::ServerContext* context,
                             const ::google::protobuf::Empty* request,
                             ::carcrash::Vehicles* response) final;
  ::grpc::Status UpdateVehicle(::grpc::ServerContext* context,
                               const ::carcrash::VehicleWithId* request,
                               ::google::protobuf::Empty* response) final;
  ::grpc::Status RegisterVehicle(::grpc::ServerContext* context,
                                 const ::carcrash::VehicleWithId* request,
                                 ::carcrash::Id* response) final;
  ::grpc::Status UnregisterVehicle(::grpc::ServerContext* context,
                                   const ::carcrash::Id* request,
                                   ::carcrash::Id* response) final;

 private:
  void checkForCollisions();

 private:
  std::unordered_map<uint32_t, Rectangle> vehicles_;
};

class Server final {
 public:
  explicit Server(std::string server_address = "0.0.0.0:50051");
  ~Server();
  Server(const Server&) = delete;
  Server(Server&&) = delete;
  Server operator=(const Server&) = delete;
  Server operator=(Server&&) = delete;

  void run();

 private:
  std::string server_address_;
  CCGRPCService service_;
  std::unique_ptr<grpc::Server> server_;
  std::atomic_uint32_t latest_id_;
};

}  // namespace CC

#endif  // CC_SERVER_HPP_
