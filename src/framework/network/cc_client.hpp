#ifndef CC_CLIENT_HPP_
#define CC_CLIENT_HPP_

#include <grpcpp/grpcpp.h>
#include "car_crash.grpc.pb.h"

namespace CC {

class Client {
 public:
  explicit Client(std::shared_ptr<::grpc::Channel>){}
};

};

#endif //CC_CLIENT_HPP_
