#ifndef CAR_CRASH_SRC_FRAMEWORK_DETAILS_MAINLOOP_HPP_
#define CAR_CRASH_SRC_FRAMEWORK_DETAILS_MAINLOOP_HPP_

#include <cstdint>

#include "../utilities/client_config.hpp"

namespace CC {

    bool mainLoop(const ClientConfig &config = ClientConfig{});

}  // namespace CC

#endif  // CAR_CRASH_SRC_FRAMEWORK_DETAILS_MAINLOOP_HPP_
