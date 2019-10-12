#include <iostream>
#include <cmath>
#include <memory>

#include <SFML/Graphics.hpp>
#include <wrappers/graphics.hpp>

#include "collision_detection.hpp"
#include "i_game_application.hpp"
#include "input.hpp"

namespace Game::Details { namespace {

constexpr uint32_t window_width = 800;
constexpr uint32_t window_height = 600;
const std::string window_name = "Car Crash";
constexpr uint32_t frame_rate = 60u;
constexpr float moving_speed = 2.5f;

std::unique_ptr<Game::Wrappers::Graphics> window = nullptr;
IGameApplicationPtr game_application = nullptr;

constexpr float getAngle(float degrees) {
  return degrees * static_cast<float>(M_PI) / 180.f;
}

constexpr Input::Key translateToGameInput(sf::Keyboard::Key key) {
  return Input::Key(key);
}

bool startUp() {
  window = std::make_unique<Game::Wrappers::Graphics>(sf::VideoMode(window_width, window_height), window_name);
  return window != nullptr;
}

void shutdown() {}

} }

namespace Game { IGameApplicationPtr createGameApplication(); }

int mainLoop() {
  using namespace Game::Details;
  if (!startUp()) { return -1; }
  window->setFramerateLimit(frame_rate);

  game_application = Game::createGameApplication();

  game_application->onStartup();

  sf::RectangleShape rectangle(sf::Vector2f(120, 50));
  rectangle.setFillColor(sf::Color::Blue);
  sf::RectangleShape rectangle2(sf::Vector2f(120, 50));
  rectangle2.setFillColor(sf::Color::Green);
  rectangle.setPosition({201, 221});
  rectangle2.setPosition({250, 100});
  rectangle.setOrigin({rectangle.getSize().x / 4, rectangle.getSize().y / 2}); // TODO: x / 4 caused collision error
  rectangle2.setOrigin({rectangle2.getSize().x / 2, rectangle2.getSize().y / 2});
  rectangle2.setRotation(-45);

  bool move_forward = false;
  bool move_backward = false;
  bool move_left = false;
  bool move_right = false;
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
          switch (event.key.code) {
            case sf::Keyboard::Left: {
              rectangle.setPosition({rectangle.getPosition().x - moving_speed, rectangle.getPosition().y});
            }
              break;
            case sf::Keyboard::Up: {
              rectangle.setPosition({rectangle.getPosition().x, rectangle.getPosition().y - moving_speed});
            }
              break;
            case sf::Keyboard::Right: {
              rectangle.setPosition({rectangle.getPosition().x + moving_speed, rectangle.getPosition().y});
            }
              break;
            case sf::Keyboard::Down: {
              rectangle.setPosition({rectangle.getPosition().x, rectangle.getPosition().y + moving_speed});
            }
              break;
            case sf::Keyboard::Escape: {
              window->close();
            }
              break;
            case sf::Keyboard::R:move_right = true;
              break;
            case sf::Keyboard::E:move_left = true;
              break;
            case sf::Keyboard::W: {
              std::cout << "shape position: " << rectangle.getPosition().x << ", " << rectangle.getPosition().y << '\n';
            }
              break;
            case sf::Keyboard::A:move_forward = true;
              break;
            case sf::Keyboard::Q:move_backward = true;
              break;
            case sf::Keyboard::P: {
              print(rectangle, rectangle2);
            }
              break;
            default:break;
          }
        }
          break;

        case sf::Event::KeyReleased: {
          Game::Input::Keyboard input{Game::Input::KeyState::Up, translateToGameInput(event.key.code)};
          game_application->onInput(input);


          switch (event.key.code) {
            case sf::Keyboard::A:move_forward = false;
              break;
            case sf::Keyboard::R:move_right = false;
              break;
            case sf::Keyboard::E:move_left = false;
              break;
            case sf::Keyboard::Q:move_backward = false;
              break;
            default:break;
          }
        }

          break;

          // we don't process other types of events
        default:break;
      }
    }

    if (move_forward) {
      float x = rectangle.getPosition().x + moving_speed * std::cos(getAngle(rectangle.getRotation()));
      float y = rectangle.getPosition().y + moving_speed * std::sin(getAngle(rectangle.getRotation()));
      rectangle.setPosition({x, y});
      if (move_left) {
        rectangle.rotate(-2);
      }
      if (move_right) {
        rectangle.rotate(2);
      }
    }

    if (move_backward) {
      float x = rectangle.getPosition().x - moving_speed * std::cos(getAngle(rectangle.getRotation()));
      float y = rectangle.getPosition().y - moving_speed * std::sin(getAngle(rectangle.getRotation()));
      rectangle.setPosition({x, y});
      if (move_left) {
        rectangle.rotate(2);
      }
      if (move_right) {
        rectangle.rotate(-2);
      }
    }

    if (isCollided(rectangle, rectangle2)) {
      rectangle.setFillColor(sf::Color::Red);
    } else {
      rectangle.setFillColor(sf::Color::Blue);
    }

    window->clear();
    game_application->onDraw(window.get());

    window->draw(rectangle2);
    window->draw(rectangle);

    window->display();
    game_application->onUpdate();


  }
  game_application->onShutdown();
  shutdown();

  return 0;
}

int main() {
  return mainLoop();
}
