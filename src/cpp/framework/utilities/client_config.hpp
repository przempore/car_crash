#ifndef CAR_CRASH_SRC_FRAMEWORK_CLIENT_CONFIG_HPP_
#define CAR_CRASH_SRC_FRAMEWORK_CLIENT_CONFIG_HPP_

#include <string>

namespace CC {

struct ClientConfig {
    uint32_t width = 800;
    uint32_t height = 600;
    std::string name = "Car Crash";
    uint32_t frame_rate = 60u;
    std::string ip = "localhost:50051";
};

}  // namespace CC

#endif  // CAR_CRASH_SRC_FRAMEWORK_CLIENT_CONFIG_HPP_
