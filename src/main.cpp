#include <iostream>
#include <memory>

#include <SFML/Graphics.hpp>
#include <wrappers/graphics.hpp>

#include "i_game_application.hpp"
#include "input.hpp"

namespace Game::Details { namespace {

constexpr uint32_t window_width = 800;
constexpr uint32_t window_height = 600;
const std::string window_name = "Car Crash";
constexpr uint32_t frame_rate = 60u;

std::unique_ptr<Game::Wrappers::Graphics> window = nullptr;
IGameApplicationPtr game_application = nullptr;

constexpr Input::Key translateToGameInput(sf::Keyboard::Key key) {
  return Input::Key(key);
}

bool startUp() {
  window = std::make_unique<Game::Wrappers::Graphics>(sf::VideoMode(window_width, window_height), window_name);
  return window != nullptr;
}

void shutdown() {}

} /* namespace Game::Details */ }

namespace Game { IGameApplicationPtr createGameApplication(); }

int main() {
  using namespace Game::Details;
  if (!startUp()) { return -1; }
  window->setFramerateLimit(frame_rate);

  game_application = Game::createGameApplication();

  game_application->onStartup();

  while (window->isOpen()) {
    sf::Event event{};
    while (window->pollEvent(event)) {
      // check the type of the event...
      switch (event.type) {
        // window closed
        case sf::Event::Closed:window->close();
          return 0;

          // key pressed
        case sf::Event::KeyPressed: {
          Game::Input::Keyboard input{Game::Input::KeyState::Down, translateToGameInput(event.key.code)};
          game_application->onInput(input);
        }
          break;

        case sf::Event::KeyReleased: {
          Game::Input::Keyboard input{Game::Input::KeyState::Up, translateToGameInput(event.key.code)};
          game_application->onInput(input);
        }

          break;

          // we don't process other types of events
        default:break;
      }
    }
    window->clear();
    game_application->onDraw(window.get());

    window->display();
    game_application->onUpdate();


  }
  game_application->onShutdown();
  shutdown();

  return 0;
}
