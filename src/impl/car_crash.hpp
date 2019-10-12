#ifndef CAR_CRASH_SRC_IMPL_CAR_CRASH_HPP_
#define CAR_CRASH_SRC_IMPL_CAR_CRASH_HPP_

#include <i_game_application.hpp>

namespace CC {

class CarCrash : public Game::IGameApplication {
 public:
  void onStartup() override;
  void onShutdown() override;
  void onUpdate() override;
  void onDraw(Game::Wrappers::Graphics *target) override;
  void onInput(const Game::Input::Keyboard keyboard) override;
};

}

#endif //CAR_CRASH_SRC_IMPL_CAR_CRASH_HPP_
