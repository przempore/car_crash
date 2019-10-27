#ifndef CAR_CRASH_SRC_FRAMEWORK_DETAILS_MAINLOOP_HPP_
#define CAR_CRASH_SRC_FRAMEWORK_DETAILS_MAINLOOP_HPP_

#include <cstdint>
#include <string>

struct GraphicsWindowConfig {
  uint32_t width = 800;
  uint32_t height = 600;
  std::string name = "Car Crash";
  uint32_t frame_rate = 60u;
};

bool mainLoop(const GraphicsWindowConfig &config = GraphicsWindowConfig{});

#endif //CAR_CRASH_SRC_FRAMEWORK_DETAILS_MAINLOOP_HPP_
