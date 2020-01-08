#ifndef CAR_CRASH_SRC_GAME_I_GAME_APPLICATION_HPP_
#define CAR_CRASH_SRC_GAME_I_GAME_APPLICATION_HPP_

#include <memory>

#include "graphics/render_window.hpp"
#include "input.hpp"

namespace Game {

class IGameApplication {
 public:
  virtual ~IGameApplication() = default;

 public:
  virtual void onStartup() = 0;
  virtual void onShutdown() = 0;
  virtual void onUpdate() = 0;
  virtual void onDraw(Game::Wrappers::RenderWindow& target) = 0;
  virtual void onInput(const Input::Keyboard) = 0;
};

using IGameApplicationPtr = std::shared_ptr<IGameApplication>;

}  // namespace Game

#endif  // CAR_CRASH_SRC_GAME_I_GAME_APPLICATION_HPP_
