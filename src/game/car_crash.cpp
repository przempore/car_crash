#define _USE_MATH_DEFINES
#include "car_crash.hpp"

#include <memory>
#include <iostream>
#include <cmath>

#include <SFML/Graphics/Color.hpp>
#include "collision_detection.hpp"
#include "../framework/network/rectangle.hpp"

namespace {

constexpr float getAngle(float degrees) {
  return degrees * static_cast<float>(M_PI) / 180.f;
}

CC::Rectangle::Color translateSfColorToGrpcColor(sf::Color color) {
  switch (color.toInteger()) {
    case 1: return CC::Rectangle::Color::Black;
    case 2: return CC::Rectangle::Color::White;
    case 3: return CC::Rectangle::Color::Red;
    case 4: return CC::Rectangle::Color::Green;
    case 5: return CC::Rectangle::Color::Blue;
    case 6: return CC::Rectangle::Color::Yellow;
    case 7: return CC::Rectangle::Color::Magenta;
    case 8: return CC::Rectangle::Color::Cyan;
    case 9: return CC::Rectangle::Color::Transparent;
  }

  return CC::Rectangle::Color::Black;
}

}

namespace CC {

CarCrash::CarCrash() : rectangles_{},
                       move_forward_{false},
                       move_backward_{false},
                       move_left_{false},
                       move_right_{false},
                       close_window_{false},
                       moving_speed_{2.5f} {
  rectangles_.emplace_back(sf::Vector2f(120, 50));
  rectangles_.emplace_back(sf::Vector2f(120, 50));
  rectangles_[0].setFillColor(sf::Color::Blue);
  rectangles_[1].setFillColor(sf::Color::Green);
  rectangles_[0].setPosition({201, 221});
  rectangles_[1].setPosition({250, 100});
  rectangles_[0].setOrigin({rectangles_[0].getSize().x / 4,  // TODO: x / 4 caused collision error
                            rectangles_[0].getSize().y / 2});
  rectangles_[1].setOrigin({rectangles_[1].getSize().x / 2, rectangles_[1].getSize().y / 2});
  rectangles_[1].setRotation(-45);
}

void CarCrash::onStartup() {
  auto a = client_.getVehicles();

  uint32_t id = client_.getId();
  std::cout << __FILE__ << ':' << __LINE__ << " | void CarCrash::onStartup()\n";

  Rectangle r{id, {rectangles_[0].getPosition().x, rectangles_[0].getPosition().y},
              rectangles_[0].getRotation(),
              {rectangles_[0].getSize().x, rectangles_[0].getSize().y},
              translateSfColorToGrpcColor(rectangles_[0].getFillColor())};
  client_.registerVehicle(r);

}

void CarCrash::onShutdown() {}

void CarCrash::onUpdate() {
  if (move_forward_) {
    float x = rectangles_[0].getPosition().x + moving_speed_ * std::cos(getAngle(rectangles_[0].getRotation()));
    float y = rectangles_[0].getPosition().y + moving_speed_ * std::sin(getAngle(rectangles_[0].getRotation()));
    rectangles_[0].setPosition({x, y});
    if (move_left_) {
      rectangles_[0].rotate(-2);
    }
    if (move_right_) {
      rectangles_[0].rotate(2);
    }
  }

  if (move_backward_) {
    float x = rectangles_[0].getPosition().x - moving_speed_ * std::cos(getAngle(rectangles_[0].getRotation()));
    float y = rectangles_[0].getPosition().y - moving_speed_ * std::sin(getAngle(rectangles_[0].getRotation()));
    rectangles_[0].setPosition({x, y});
    if (move_left_) {
      rectangles_[0].rotate(2);
    }
    if (move_right_) {
      rectangles_[0].rotate(-2);
    }
  }

  if (isCollided(rectangles_[0], rectangles_[1])) {
    rectangles_[0].setFillColor(sf::Color::Red);
  } else {
    rectangles_[0].setFillColor(sf::Color::Blue);
  }

}

void CarCrash::onDraw(Game::Wrappers::Graphics &target) {
  for (auto it = rectangles_.rbegin(); it != rectangles_.rend(); ++it) {
    target.draw(*it);
  }
  if (close_window_) {
    target.close();
  }
}

void CarCrash::onInput(const Game::Input::Keyboard keyboard) {
  if (keyboard.state == Game::Input::KeyState::Down) {
    switch (keyboard.code) {
      case Game::Input::Key::Left: {
        rectangles_[0].setPosition({rectangles_[0].getPosition().x - moving_speed_, rectangles_[0].getPosition().y});
      }
        break;
      case Game::Input::Key::Up: {
        rectangles_[0].setPosition({rectangles_[0].getPosition().x, rectangles_[0].getPosition().y - moving_speed_});
      }
        break;
      case Game::Input::Key::Right: {
        rectangles_[0].setPosition({rectangles_[0].getPosition().x + moving_speed_, rectangles_[0].getPosition().y});
      }
        break;
      case Game::Input::Key::Down: {
        rectangles_[0].setPosition({rectangles_[0].getPosition().x, rectangles_[0].getPosition().y + moving_speed_});
      }
        break;
      case Game::Input::Key::Escape:close_window_ = true;
        break;
      case Game::Input::Key::R:move_right_ = true;
        break;
      case Game::Input::Key::E:move_left_ = true;
        break;
      case Game::Input::Key::W: {
        std::cout << "shape position: " << rectangles_[0].getPosition().x << ", " << rectangles_[0].getPosition().y
                  << '\n';
      }
        break;
      case Game::Input::Key::A:move_forward_ = true;
        break;
      case Game::Input::Key::Q:move_backward_ = true;
        break;
      default:break;
    }
  } else {

    switch (keyboard.code) {
      case Game::Input::Key::A:move_forward_ = false;
        break;
      case Game::Input::Key::R:move_right_ = false;
        break;
      case Game::Input::Key::E:move_left_ = false;
        break;
      case Game::Input::Key::Q:move_backward_ = false;
        break;
      default:break;
    }
  }
}

}

namespace Game {

Game::IGameApplicationPtr createGameApplication() {
  return std::make_shared<CC::CarCrash>();
}

}
