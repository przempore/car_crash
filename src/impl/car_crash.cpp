#include "car_crash.hpp"

#include <memory>
#include <iostream>

namespace CC {

void CarCrash::onStartup() {
  std::cout << __PRETTY_FUNCTION__ << '\n';
}

void CarCrash::onShutdown() {}

void CarCrash::onUpdate() {}

void CarCrash::onDraw(Game::Wrappers::Graphics *target) {}

void CarCrash::onInput(const Game::Input::Keyboard keyboard) {}

}

namespace Game {

Game::IGameApplicationPtr createGameApplication() {
  return std::make_shared<CC::CarCrash>();
}

}
