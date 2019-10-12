#ifndef CAR_CRASH_SRC_GAME_GAME_APPLICATION_HPP_
#define CAR_CRASH_SRC_GAME_GAME_APPLICATION_HPP_

#include <memory>

#include "input.hpp"

namespace Game {

class GameApplication {
 public:
  void onStartup();
  void onShutdown();
  void onUpdate();
  void onDraw();
  void onEvent(const Input::Keyboard);
  void onInput();
};

using GameApplicationPtr = std::shared_ptr<GameApplication>;

}

#endif //CAR_CRASH_SRC_GAME_GAME_APPLICATION_HPP_
