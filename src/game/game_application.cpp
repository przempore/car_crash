#include "game_application.hpp"

namespace Game {

GameApplicationPtr createGameApplication() {
  return std::make_shared<GameApplication>();
}

void GameApplication::onEvent(const Input::Keyboard input) {

}

}
