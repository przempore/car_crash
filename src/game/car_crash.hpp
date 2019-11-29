#ifndef CAR_CRASH_SRC_IMPL_CAR_CRASH_HPP_
#define CAR_CRASH_SRC_IMPL_CAR_CRASH_HPP_

#include <vector>
#include <string>

#include <i_game_application.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <network/cc_client.hpp>


namespace CC {

class CarCrash : public Game::IGameApplication {
 public:
  explicit CarCrash(const std::string& ip);
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
  void move();

  enum class MoveDirections : uint32_t {
    forward = 1 << 0,
    right = 1 << 1,
    backwards = 1 << 2,
    left = 1 << 3,
    stay_still = 1 << 4
  };

  void appendMoveDirection(MoveDirections dir);
  void removeMoveDirection(MoveDirections dir);
  bool checkMoveDirection(MoveDirections dir);

 private:
  sf::RectangleShape rectangle_;
  uint32_t rectangle_id_;

  bool close_window_;
  const float moving_speed_;
  uint32_t moving_direction_;
  CC::Client client_;
};

}

#endif //CAR_CRASH_SRC_IMPL_CAR_CRASH_HPP_
