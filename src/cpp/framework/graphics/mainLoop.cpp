#include "mainLoop.hpp"

#include "../i_game_application.hpp"
#include "../utilities/input.hpp"
#include "render_window.hpp"

namespace Game {
IGameApplicationPtr createGameApplication(const std::string& ip);
}

namespace CC {

bool mainLoop(const ClientConfig& config) {
  Game::Wrappers::RenderWindow window{
      sf::VideoMode(config.width, config.height), config.name};

  window.setFramerateLimit(config.frame_rate);
  auto game_application = Game::createGameApplication(config.ip);
  game_application->onStartup();

  while (window.isOpen()) {
    sf::Event event{};
    while (window.pollEvent(event)) {
      switch (event.type) {
        case sf::Event::Closed:
          window.close();
          return true;
        case sf::Event::KeyPressed:
          game_application->onInput(
              {Game::Input::KeyState::Down, Game::Input::Key(event.key.code)});
          break;
        case sf::Event::KeyReleased:
          game_application->onInput(
              {Game::Input::KeyState::Up, Game::Input::Key(event.key.code)});
          break;
        default:
          break;
      }
    }
    window.clear();
    game_application->onDraw(window);

    window.display();
    game_application->onUpdate();
  }
  game_application->onShutdown();

  return true;
}

}  // namespace CC
