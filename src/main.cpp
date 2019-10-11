#include <iostream>
#include <cmath>

#include <SFML/Graphics.hpp>

#include "collision_detection.hpp"


double getAngle(double a) {
  return a * M_PI;
}

int mainLoop() {
  sf::RenderWindow window(sf::VideoMode(600, 400), "SFML works!");
  window.setFramerateLimit(60);
  constexpr float moving_speed = 5.f;

  sf::RectangleShape rectangle(sf::Vector2f(120, 50));
  rectangle.setFillColor(sf::Color::Blue);
  sf::RectangleShape rectangle2(sf::Vector2f(120, 50));
  rectangle2.setFillColor(sf::Color::Green);
  rectangle.setPosition({201, 221});
  rectangle2.setPosition({250, 100});
  double angle = getAngle(1.);
  rectangle.setOrigin({rectangle.getSize().x / 2, rectangle.getSize().y / 2});
  rectangle2.setOrigin({rectangle2.getSize().x / 2, rectangle2.getSize().y / 2});
  rectangle2.setRotation(-45);

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      // check the type of the event...
      switch (event.type) {
        // window closed
        case sf::Event::Closed: window.close();
          return 0;

          // key pressed
        case sf::Event::KeyPressed: {
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
              window.close();
            }
              break;
            case sf::Keyboard::R: {
              rectangle.rotate(2);
              std::cout << "rectangle.getRotation: " << rectangle.getRotation() << '\n';
            }
              break;
            case sf::Keyboard::E: {
              rectangle.rotate(-2);
              std::cout << "rectangle.getRotation: " << rectangle.getRotation() << '\n';
            }
              break;
            case sf::Keyboard::W: {
              std::cout << "shape position: " << rectangle.getPosition().x << ", " << rectangle.getPosition().y << '\n';
            }
              break;
            case sf::Keyboard::P: {
              print(rectangle, rectangle2);
            }
              break;
            default: break;
          }
        }

          break;

          // we don't process other types of events
        default: break;
      }
    }

    if (isCollided(rectangle, rectangle2)) {
      rectangle.setFillColor(sf::Color::Red);
    } else {
      rectangle.setFillColor(sf::Color::Blue);
    }

    window.clear();
    window.draw(rectangle2);
    window.draw(rectangle);
    window.display();
  }

  return 0;
}

int main(int argc, char const *argv[]) {
  return mainLoop();
}
