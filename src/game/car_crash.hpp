#ifndef CAR_CRASH_SRC_IMPL_CAR_CRASH_HPP_
#define CAR_CRASH_SRC_IMPL_CAR_CRASH_HPP_

#include <vector>

#include <i_game_application.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

namespace CC {

class CarCrash : public Game::IGameApplication {
 public:
  CarCrash();

 public:
  void onStartup() override;
  void onShutdown() override;
  void onUpdate() override;
  void onDraw(Game::Wrappers::Graphics *target) override;
  void onInput(const Game::Input::Keyboard keyboard) override;

 private:
  std::vector<sf::RectangleShape> rectangles_;

  bool move_forward_;
  bool move_backward_;
  bool move_left_;
  bool move_right_;
  bool close_window_;
  const float moving_speed_;
};

}

#endif //CAR_CRASH_SRC_IMPL_CAR_CRASH_HPP_
