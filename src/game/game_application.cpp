#include "game_application.hpp"

namespace Game {

GameApplicationPtr createGameApplication() {
  return std::make_shared<GameApplication>();
}

void GameApplication::onStartup() {

}

void GameApplication::onShutdown() {

}

void GameApplication::onDraw(Game::Wrappers::Graphics* target) {

}

void GameApplication::onInput(const Input::Keyboard input) {

}
void GameApplication::onUpdate() {

}

}
