#ifndef CAR_CRASH_SRC_IMPL_CAR_CRASH_HPP_
#define CAR_CRASH_SRC_IMPL_CAR_CRASH_HPP_

#include <vector>

#include <i_game_application.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <network/cc_client.hpp>


namespace CC {

class CarCrash : public Game::IGameApplication {
 public:
  explicit CarCrash();
  ~CarCrash();
  CarCrash(const CarCrash&) = delete;
  CarCrash(CarCrash&&) = delete;
  CarCrash operator=(const CarCrash&) = delete;
  CarCrash operator=(CarCrash&&) = delete;


 public:
  void onStartup() override;
  void onShutdown() override;
  void onUpdate() override;
  void onDraw(Game::Wrappers::Graphics &target) override;
  void onInput(const Game::Input::Keyboard keyboard) override;

 private:
  sf::RectangleShape rectangle_;
  uint32_t rectangle_id_;
//  std::vector<sf::RectangleShape> rectangles_; // todo: to remove, client will have only one rectangle to control

  bool move_forward_;
  bool move_backward_;
  bool move_left_;
  bool move_right_;
  bool close_window_;
  const float moving_speed_;
  CC::Client client_;
};

}

#endif //CAR_CRASH_SRC_IMPL_CAR_CRASH_HPP_
