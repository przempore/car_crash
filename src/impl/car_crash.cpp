#include "car_crash.hpp"

#include <memory>
#include <iostream>
#include <cmath>

#include "collision_detection.hpp"
#include <SFML/Graphics/Color.hpp>

namespace {

constexpr float getAngle(float degrees) {
  return degrees * static_cast<float>(M_PI) / 180.f;
}

}

namespace CC {

CarCrash::CarCrash() : rectangle_{sf::Vector2f(120, 50)},
                       rectangle2_{sf::Vector2f(120, 50)},
                       move_forward_{false},
                       move_backward_{false},
                       move_left_{false},
                       move_right_{false},
                       close_window_{false},
                       moving_speed_{2.5f} {
  rectangle_.setFillColor(sf::Color::Blue);
  rectangle2_.setFillColor(sf::Color::Green);
  rectangle_.setPosition({201, 221});
  rectangle2_.setPosition({250, 100});
  rectangle_.setOrigin({rectangle_.getSize().x / 4, rectangle_.getSize().y / 2}); // TODO: x / 4 caused collision error
  rectangle2_.setOrigin({rectangle2_.getSize().x / 2, rectangle2_.getSize().y / 2});
  rectangle2_.setRotation(-45);
}

void CarCrash::onStartup() {
  std::cout << __PRETTY_FUNCTION__ << '\n';
}

void CarCrash::onShutdown() {}

void CarCrash::onUpdate() {
  if (move_forward_) {
    float x = rectangle_.getPosition().x + moving_speed_ * std::cos(getAngle(rectangle_.getRotation()));
    float y = rectangle_.getPosition().y + moving_speed_ * std::sin(getAngle(rectangle_.getRotation()));
    rectangle_.setPosition({x, y});
    if (move_left_) {
      rectangle_.rotate(-2);
    }
    if (move_right_) {
      rectangle_.rotate(2);
    }
  }

  if (move_backward_) {
    float x = rectangle_.getPosition().x - moving_speed_ * std::cos(getAngle(rectangle_.getRotation()));
    float y = rectangle_.getPosition().y - moving_speed_ * std::sin(getAngle(rectangle_.getRotation()));
    rectangle_.setPosition({x, y});
    if (move_left_) {
      rectangle_.rotate(2);
    }
    if (move_right_) {
      rectangle_.rotate(-2);
    }
  }

  if (isCollided(rectangle_, rectangle2_)) {
    rectangle_.setFillColor(sf::Color::Red);
  } else {
    rectangle_.setFillColor(sf::Color::Blue);
  }

}

void CarCrash::onDraw(Game::Wrappers::Graphics *target) {
  target->draw(rectangle2_);
  target->draw(rectangle_);
  if (close_window_) {
    target->close();
  }
}

void CarCrash::onInput(const Game::Input::Keyboard keyboard) {
  if (keyboard.state == Game::Input::KeyState::Down) {
    switch (keyboard.code) {
      case Game::Input::Key::Left: {
        rectangle_.setPosition({rectangle_.getPosition().x - moving_speed_, rectangle_.getPosition().y});
      }
        break;
      case Game::Input::Key::Up: {
        rectangle_.setPosition({rectangle_.getPosition().x, rectangle_.getPosition().y - moving_speed_});
      }
        break;
      case Game::Input::Key::Right: {
        rectangle_.setPosition({rectangle_.getPosition().x + moving_speed_, rectangle_.getPosition().y});
      }
        break;
      case Game::Input::Key::Down: {
        rectangle_.setPosition({rectangle_.getPosition().x, rectangle_.getPosition().y + moving_speed_});
      }
        break;
      case Game::Input::Key::Escape:close_window_ = true;
        break;
      case Game::Input::Key::R:move_right_ = true;
        break;
      case Game::Input::Key::E:move_left_ = true;
        break;
      case Game::Input::Key::W: {
        std::cout << "shape position: " << rectangle_.getPosition().x << ", " << rectangle_.getPosition().y << '\n';
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
